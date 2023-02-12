import java.net.*;
import java.io.*;

    public class Client {
        private static final int SLEEP_TIME = 500;
        private static final int PORT = 9876;
        public static void main(String args[]) throws IOException, InterruptedException {

            BufferedReader br =new BufferedReader(new InputStreamReader(System.in));
            
            while(true) {
                Socket socket = new Socket("localhost", PORT);
                InputStream is = socket.getInputStream();
                OutputStream os = socket.getOutputStream();

                Writer writer = new OutputStreamWriter(os, "US-ASCII");
                PrintWriter out = new PrintWriter(writer, true);

                System.out.println("Your message to the server: ");
                Thread.sleep(1000);
                String clientCommand = br.readLine();

                out.println(clientCommand);
                BufferedReader in = new BufferedReader(new InputStreamReader(is, "US-ASCII"));

                String line;
                while ((line = in.readLine()) != null) {
                    System.out.println("Server's answer: " + line);
                }

                socket.close();
                Thread.sleep(SLEEP_TIME);
            }
        }
   }