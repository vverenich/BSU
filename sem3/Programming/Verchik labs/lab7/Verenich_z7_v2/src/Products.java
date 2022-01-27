/*
import java.io.*;
import java.util.*;

public class Products {
    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {				
                if ( args[0].equals("-?") || args[0].equals("-h")) {
                    System.out.println( 
                        "Syntax:\n" +
                        "\t-a  [file [encoding]] - append data\n" +
                        "\t-az [file [encoding]] - append data, compress every record\n" +
                        "\t-d                    - clear all data\n" +
                        "\t-dk  {i|a|n} key      - clear data by key\n" +
                        "\t-p                    - print data unsorted\n" +
                        "\t-ps  {c|s|n}          - print data sorted by code/store/name\n" +
                        "\t-psr {c|s|n}          - print data reverse sorted by code/store/name\n" +
                        "\t-f   {c|s|n} key      - find record by key\n"+
                        "\t-fr  {c|s|n} key      - find records > key\n"+
                        "\t-fl  {c|s|n} key      - find records < key\n"+
                        "\t-?, -h                - command line syntax\n"
                    );
                }
                else if ( args[0].equals( "-a" )) {
                    // Append file with new object from System.in
                    // -a [file [encoding]]
                    appendFile( args, false );
                }
                else if ( args[0].equals( "-az" )) {
                    // Append file with compressed new object from System.in
                    // -az [file [encoding]]
                    appendFile( args, true );
                }
                else if ( args[0].equals( "-p" )) {
                    // Prints data file
                    printFile();
                }
                else if ( args[0].equals( "-ps" )) {
                    // Prints data file sorted by key
                    if ( printFile( args, false )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-psr" )) {
                    // Prints data file reverse-sorted by key
                    if ( printFile( args, true )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-d" )) {
                    // delete files
                    if ( args.length != 1 ) {
                        System.err.println("Invalid number of arguments");
                        System.exit(1);;
                    }
                    deleteFile();
                }
                else if ( args[0].equals( "-dk" )) {
                    // Delete records by key
                    if ( deleteFile( args )== false ) {
                        System.exit(1);						
                    }
                }
                else if ( args[0].equals( "-f" )) {
                    // Find record(s) by key
                    if ( findByKey( args )== false ) {
                        System.exit(1);
                    }
                }
                else if ( args[0].equals( "-fr" )) {
                    // Find record(s) by key large then key 
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
                System.err.println( "Products: Nothing to do! Enter -? for options" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.err.println( "Products finished..." );	
        System.exit(0);
    }

    static final String filename    = "Products.dat";
    static final String filenameBak = "Products.~dat";
    static final String idxname     = "Products.idx";
    static final String idxnameBak  = "Products.~idx";
	
    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream productOut = System.out;
	
    static Product readProduct( Scanner fin ) throws IOException {	
        return Product.nextRead( fin, productOut ) 
                ? Product.read( fin, productOut ) : null;
    }

    private static void deleteBackup() {
        new File( filenameBak ).delete();
        new File( idxnameBak ).delete();				
    }
	
    static void deleteFile() {
        deleteBackup();
        new File( filename ).delete();
        new File( idxname ).delete();
    }
	
    private static void backup() {
        deleteBackup();
        new File( filename ).renameTo( new File( filenameBak ));
        new File( idxname ).renameTo( new File( idxnameBak ));
    }

    static boolean deleteFile( String[] args ) 
            throws ClassNotFoundException, IOException, KeyNotUniqueException {
        //-dk  {c|s|n} key      - clear data by key
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
                Product product = (Product) 
                Buffer.readObject( fileBak, pos, wasZipped );
                if ( Arrays.binarySearch(poss, pos) < 0 ) { // if not found in deleted
                    long ptr = Buffer.writeObject( file, product, wasZipped[0] );
                    idx.put( product, ptr );
                }
             }
         }
         return true;
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
            productOut = new PrintStream("nul");
        }
        appendFile( zipped );
    }
	
    static void appendFile( Boolean zipped ) 
            throws FileNotFoundException, IOException, ClassNotFoundException, 
                KeyNotUniqueException {
        Scanner fin = new Scanner( System.in, encoding );
        productOut.println( "Enter product data: " );
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            for(;;) {
                Product product = readProduct( fin );
                if ( product == null )
                    break;
                idx.test( product );
                long pos = Buffer.writeObject( raf, product, zipped );
                idx.put( product, pos );
            }
        }
    }
	
    private static void printRecord( RandomAccessFile raf, long pos ) 
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[] {false};
        Product product = (Product) Buffer.readObject( raf, pos, wasZipped );
        if ( wasZipped[0] == true ) {
            System.out.print( " compressed" );
        }
        System.out.println( " record:\n========================= \n" + product );
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
            	System.out.print("=========================\n");
                System.out.print( "#" + (++rec ));
                printRecord( raf, pos );
            }
            System.out.flush();
        }		
    }
	
    private static IndexBase indexByArg( String arg, Index idx ) {
        IndexBase pidx = null;
        if ( arg.equals("c")) {
            pidx = idx.codes;
        } 
        else if ( arg.equals("s")) {
            pidx = idx.stores;
        } 
        else if ( arg.equals("n")) {
            pidx = idx.names;
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
*/
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class Products {
    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {				
                if ( args[0].equals("-?") || args[0].equals("-h")) {
                    System.out.println( 
                        "Syntax:\n" +
                        "\t-a  [file [encoding]]   - append data\n" +
                        "\t-d                      - clear all data\n" +
                        "\t-dk  {s|p|d|D} key      - clear data by key\n" +
                        "\t-p                      - print data unsorted\n" +
                        "\t-ps  {p|s|d|D}          - print data sorted by storeNumber/productCode/date/Days\n" +
                        "\t-psr {p|s|d|D}          - print data reverse sorted by storeNumber/productCode/date/Days\n" +
                        "\t-f   {p|s|d|D} key      - find record by key\n"+
                        "\t-fr  {p|s|d|D} key      - find records > key\n"+
                        "\t-fl  {p|s|d|D} key      - find records < key\n"+
                        "\t-?, -h                  - command line syntax\n"
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
                System.err.println( "Products: Nothing to do! Enter -? for options" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.err.println( "Products finished..." );	
        System.exit(0);
    }


    static final String filename    = "Products.dat";
    static final String filenameBak = "Products.~dat";
    static final String idxname     = "Products.idx";
    static final String idxnameBak  = "Products.~idx";
	
    // input file encoding:
    private static String encoding = "Cp866";
    private static PrintStream bookOut = System.out;
	
    static Product readProduct( Scanner fin ) throws IOException {	
        return Product.nextRead( fin, bookOut ) 
                ? Product.read( fin, bookOut ) : null;
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
				Product phone = (Product)
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
        String fileName = "Products.txt";
        Path path = Paths.get(fileName);
        Scanner fin = new Scanner(path);
        bookOut.println( "Enter product data: " );
        try ( Index idx = Index.load( idxname ); 
              RandomAccessFile raf = new RandomAccessFile( filename, "rw" )) {
            for(int i = 0; i < 5; ++i) {
                Product product = readProduct( fin );
                if ( product == null )
                    break;
                idx.test( product);
                long pos = Buffer.writeObject( raf, product, zipped );
                idx.put( product, pos );
            }
        }
    }
	
    private static void printRecord( RandomAccessFile raf, long pos ) 
            throws ClassNotFoundException, IOException {
        boolean[] wasZipped = new boolean[] {false};
        Product phone = (Product) Buffer.readObject( raf, pos, wasZipped );
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
        if ( arg.equals("p")) {
            pidx = idx.productCodes;
        } 
        else if ( arg.equals("s")) {
            pidx = idx.storeNumbers;
        } 
        else if ( arg.equals("d")) {
            pidx = idx.dates;
        } 
        else if(arg.equals("D")) {
        	pidx = idx.dayss;
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

