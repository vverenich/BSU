import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Phones {
    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {				
                if ( args[0].equals("-?") || args[0].equals("-h")) {
                    System.out.println( 
                        "Syntax:\n" +
                        "\t-a  [file [encoding]] - append data\n" +
                        "\t-d                    - clear all data\n" +
                        "\t-dk  {n|s|a} key      - clear data by key\n" +
                        "\t-p                    - print data unsorted\n" +
                        "\t-ps  {n|s|a}          - print data sorted by number/surname/adress\n" +
                        "\t-psr {n|s|a}          - print data reverse sorted by number/surname/adress\n" +
                        "\t-f   {n|s|a} key      - find record by key\n"+
                        "\t-fr  {n|s|a} key      - find records > key\n"+
                        "\t-fl  {n|s|a} key      - find records < key\n"+
                        "\t-?, -h                - command line syntax\n"
                    );
                }
                else if (args.length == 1 && (args[0].equals(("-a")) || args[0].equals("-az"))) {
                    appendFile(args, false);
                }
                else if (args.length == 1 && args[0].equals("-d")) {
                    // delete files
                    if ( args.length != 1 ) {
                        System.err.println("Invalid number of arguments");
                        System.exit(1);
                    }
                    deleteFile();
                }
                else if(args.length == 1 && args[0].equals("-p"))
                {
                    printFile();
                }
                else if (args.length == 2 && args[0].equals("-ps"))
                {
                    if( printFile(args, false) == false)
                    {
                        System.exit(1);
                    }
                }
                else if (args.length == 2 && args[0].equals("-psr"))
                {
                    if( printFile(args, true) == false)
                    {
                        System.exit(1);
                    }
                }
                else if (args.length == 3 && args[0].equals("-dk"))
                {
                   if (deleteFile(args) == false)
                   {
                       System.exit(1);
                   }
                }
                else if (args.length == 3 && args[0].equals("-f"))
                {
                   if(findByKey(args)==false){
                       System.exit(1);
                   }
                }
                else if ( args[0].equals( "-fr" )) {
                    // Find record(s) by key large than key
                    if ( findByKey( args, new KeyCompReverse() )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-fl" )) {
                    // Find record(s) by key less then key
                    if ( findByKey( args, new KeyComp() )== false ) {
                        System.exit(1);
                    }
                }
                else {
                    System.err.println( "Option is not realised: " + args[0] );
                    System.exit(1);
                }
            }
            else {
                System.err.println( "Phones: Nothing to do! Enter -? for options" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.err.println( "Phones finished..." );	
        System.exit(0);
    }


    static final String filename    = "Phones.dat";
    static final String filenameBak = "Phones.~dat";
    static final String idxname     = "Phones.idx";
    static final String idxnameBak  = "Phones.~idx";
	
    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream bookOut = System.out;
	
    static Phone readPhone( Scanner fin ) throws IOException {	
        return Phone.nextRead( fin, bookOut ) 
                ? Phone.read( fin, bookOut ) : null;
    }

    private static void deleteBackup() {
        new File( filenameBak ).delete();
        new File( idxnameBak ).delete();				
    }
	
	
    private static void backup() {
        deleteBackup();
        new File( filename ).renameTo( new File( filenameBak ));
        new File( idxname ).renameTo( new File( idxnameBak ));
    }


	static boolean deleteFile( String[] args ) throws ClassNotFoundException, IOException, KeyNotUniqueException {
		//-dk  {i|a|n} key      - clear data by key
		if ( args.length != 3 ) {
			System.err.println( "Invalid number of arguments" );
			return false;
		}
		
		long[] poss = null;
		try ( Index idx = Index.load( idxname )) {
			IndexBase pidx = indexByArg( args[1], idx );
			if ( pidx == null ) {
				return false;
			}
			if ( pidx.contains(args[2])== false ) {
				System.err.println( "Key not found: " + args[2] );
				return false;
			}
			poss = pidx.get(args[2]);
		}
		backup();
		Arrays.sort( poss );
		try ( Index idx = Index.load( idxname );
				RandomAccessFile fileBak= new RandomAccessFile(filenameBak, "rw");
				RandomAccessFile file = new RandomAccessFile( filename, "rw")) {
			boolean[] wasZipped = new boolean[] {false};
			long pos;
			while (( pos = fileBak.getFilePointer()) < fileBak.length() ) {
				Phone phone = (Phone)
						Buffer.readObject( fileBak, pos, wasZipped );
				if ( Arrays.binarySearch(poss, pos) < 0 ) { // if not found in deleted
					long ptr = Buffer.writeObject( file, phone, wasZipped[0] );
					idx.put( phone, ptr );
				}
			}
		}
		return true;
	}

	static void deleteFile() {
		new File( filenameBak ).delete();
		new File( idxnameBak ).delete();
		new File( filename ).delete();
		new File( idxname ).delete();
	}
	

    static void appendFile( String[] args, Boolean zipped ) 
            throws FileNotFoundException, IOException, ClassNotFoundException,
                KeyNotUniqueException {
        if ( args.length >= 2 ) {
            FileInputStream stdin = new FileInputStream( args[1] );
            System.setIn( stdin );
            if (args.length == 3) {
                encoding = args[2];
            }
            // hide output:
            bookOut = new PrintStream("nul");
        }
        appendFile( zipped );
    }
	
    static void appendFile( Boolean zipped ) 
            throws FileNotFoundException, IOException, ClassNotFoundException, 
                KeyNotUniqueException {
        String fileName = "People.txt";
        Path path = Paths.get(fileName);
        Scanner fin = new Scanner(path);
        bookOut.println( "Enter book data: " );
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            for(int i = 0; i < 4; ++i) {
                Phone phone = readPhone( fin );
                if ( phone == null )
                    break;
                idx.test( phone );
                long pos = Buffer.writeObject( raf, phone, zipped );
                idx.put( phone, pos );
            }
        }
    }
	
    private static void printRecord( RandomAccessFile raf, long pos ) 
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[] {false};
        Phone phone = (Phone) Buffer.readObject( raf, pos, wasZipped );
        if ( wasZipped[0] == true ) {
            System.out.print( " compressed" );
        }
        System.out.println( " record at position "+ pos + ": \n" + phone );	
    }
	
    private static void printRecord( RandomAccessFile raf, String key, 
            IndexBase pidx ) throws ClassNotFoundException, IOException {
        long[] poss = pidx.get( key );
        for ( long pos : poss ) {
            System.out.print( "*** Key: " +  key + " points to" );
            printRecord( raf, pos );
        }		
    }
	
    static void printFile() 
            throws FileNotFoundException, IOException, ClassNotFoundException {
        long pos;
        int rec = 0;
        try ( RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            while (( pos = raf.getFilePointer()) < raf.length() ) {
                System.out.print( "#" + (++rec ));
                printRecord( raf, pos );
            }
            System.out.flush();
        }		
    }
	
    private static IndexBase indexByArg( String arg, Index idx ) {
        IndexBase pidx = null;
        if ( arg.equals("n")) {
            pidx = idx.number;
        } 
        else if ( arg.equals("s")) {
            pidx = idx.surname;
        } 
        else if ( arg.equals("a")) {
            pidx = idx.adress;
        } 
        else {
            System.err.println( "Invalid index specified: " + arg );
        }
        return pidx;
    }
	
    static boolean printFile( String[] args, boolean reverse ) 
            throws ClassNotFoundException, IOException {
        if ( args.length != 2 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx == null ) {
                return false;
            }
            String[] keys = 
                pidx.getKeys( reverse ? new KeyCompReverse() : new KeyComp() );
            for ( String key : keys ) {
                printRecord( raf, key, pidx );
            }
        }
        return true;
    }
	
    static boolean findByKey( String[] args ) 
            throws ClassNotFoundException, IOException {
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx.contains(args[2])== false ) {
                System.err.println( "Key not found: " + args[2] );
                return false;				
            }
            printRecord( raf, args[2], pidx );
        }
        return true;	
    }
	
    static boolean findByKey( String[] args, Comparator<String> comp ) 
            throws ClassNotFoundException, IOException {
        if ( args.length != 3 ) {
            System.err.println( "Invalid number of arguments" );
            return false;
        }
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            IndexBase pidx = indexByArg( args[1], idx );
            if ( pidx.contains(args[2])== false ) {
                System.err.println( "Key not found: " + args[2] );
                return false;				
            }
            String[] keys = pidx.getKeys( comp );
            for ( int i = 0; i < keys.length; i++ ) {
                String key = keys[i];
                if ( key.equals( args[2] )) {
                    break;
                }
                printRecord( raf, key, pidx );
            }
        }
        return true;
    }
}
