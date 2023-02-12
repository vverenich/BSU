import java.io.*;
import java.net.*;
import java.nio.*;
import java.nio.channels.*;
import java.util.*;

public class Server {
        private static int PORT = 9876;
        private static int BUFFER_SIZE = 4096;

        private final static Random rowNumberRandomGenerator = new Random();
        private final static String fileWithRows = new String("D:/BSU/BSU/sem5/Web-programming/lab5_part2/project/input.txt");
        private static ArrayList<String> rowsInFile = new ArrayList<String>();

        public static void main (String args[]) throws FileNotFoundException {
            readRowsFromFile();

            ByteBuffer sharedBuffer =  ByteBuffer.allocateDirect(BUFFER_SIZE);
            Selector selector = null;
            ServerSocket serverSocket = null;

            try {
                ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
                serverSocketChannel.configureBlocking(false);
                serverSocket = serverSocketChannel.socket();

                InetSocketAddress inetSocketAddress = new InetSocketAddress(PORT);
                serverSocket.bind(inetSocketAddress);
                selector = Selector.open();
                serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
            } catch (IOException e) {
                System.err.println("Unable to setup environment");
                System.exit(-1);
            }

            try {
                while (true) {
                    int count = selector.select();
                    // нечего обрабатывать
                    if (count == 0) {
                        continue;
                    }

                    Set keySet = selector.selectedKeys();
                    Iterator itor = keySet.iterator();
                    while (itor.hasNext()) {
                        SelectionKey selectionKey = (SelectionKey) itor.next();
                        itor.remove();
                        Socket socket = null;
                        SocketChannel channel = null;

                        if (selectionKey.isAcceptable()) {
                            System.out.println("Got acceptable key");
                            try {
                                socket = serverSocket.accept();
                                System.out.println
                                    ("Connection from: " + socket);
                                channel = socket.getChannel();
                            } catch (IOException e) {
                                System.err.println("Unable to accept channel");
                                e.printStackTrace();
                                selectionKey.cancel();
                            }
                            if (channel != null) {
                                try {
                                    System.out.println("Watch for something to read");
                                    channel.configureBlocking(false);
                                    channel.register(selector, SelectionKey.OP_READ);
                                } catch (IOException e) {
                                    System.err.println("Unable to use channel");
                                    e.printStackTrace();
                                    selectionKey.cancel();
                                }
                            }
                        }
                        if (selectionKey.isReadable()) {
                            System.out.println("Reading channel");
                            SocketChannel socketChannel = (SocketChannel) selectionKey.channel();
                            sharedBuffer.clear();
                            int bytes = -1;
                            try {
                                while ((bytes = socketChannel.read(sharedBuffer)) > 0)
                                {
                                    System.out.println("Reading...");
                                    sharedBuffer.flip();
                                    while (sharedBuffer.hasRemaining()) {
                                    System.out.println("Writing...");

                                    String answerPart1 = new String("Server reply - "); 
                                    String answerPart2 = new String("Server's random row from file is - " + 
                                                                        rowsInFile.get(rowNumberRandomGenerator.nextInt(rowsInFile.size() - 1)));
                                    ByteBuffer bufPart1 = ByteBuffer.wrap(answerPart1.getBytes());
                                    ByteBuffer bufPart2 = ByteBuffer.wrap(answerPart2.getBytes());
                                
                                    socketChannel.write(bufPart1);
                                    socketChannel.write(sharedBuffer);
                                    socketChannel.write(bufPart2);
                                    //sharedBuffer.clear();
                                    //System.out.println( Arrays.toString(sharedBuffer.array()));
                                    }
                                    sharedBuffer.clear();
                                }
                            } catch (IOException e) {
                                System.err.println("Error writing back bytes");
                                e.printStackTrace();
                                selectionKey.cancel();
                            }

                            try {
                                System.out.println("Closing...");
                                socketChannel.close();
                            } catch (IOException e) {
                                e.printStackTrace();
                                selectionKey.cancel();
                            }
                        }
                        
                        System.out.println("Next...");
                    }
                }
            } catch (IOException e) {
                System.err.println("Error during select()");
                e.printStackTrace();
            }
        }

        private static void readRowsFromFile() throws FileNotFoundException 
        {
            File file = new File(fileWithRows);
            Scanner sc = new Scanner(file);
    
            while (sc.hasNextLine()) {
                rowsInFile.add(sc.nextLine());
            }

            sc.close();
        }
   }