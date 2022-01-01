import java.io.*;
import java.nio.file.Files;
import java.util.*;

public class Products {

    public static void main(String[] args) {
        try {
            if ( args.length >= 1 ) {
                if ( args[0].compareTo( "-a" )== 0 ) {
                    // Append file with new object from System.in
                    append_file();
                }
                else if ( args[0].compareTo( "-p" )== 0 ) {
                    // Prints data file
                    print_file();
                }
                else if ( args[0].compareTo( "-d" )== 0 ) {
                    // Delete data file
                    delete_file();
                }
                else {
                    System.err.println( "Option is not realised: " + args[0] );
                    System.exit(1);
                }
            }
            else {
                System.err.println( "Products: Nothing to do!" );
            }
        }
        catch ( Exception e ) {
            System.err.println( "Run/time error: " + e );
            System.exit(1);
        }
        System.out.println( "Products finished..." );	
	System.exit(0);
    }

    static final String filename = "D:\\Java(AND ALL RELATED)\\Projects\\lab_3\\Products.dat";
    private static Scanner fin = new Scanner( System.in );

    static Product read_product() {
        if ( fin.hasNextLine()) {
            return Product.read(fin);
        }
        return null;
    }
	
    static void delete_file() {
        File f = new File(filename);
        
        if(f.delete()) {;
        	System.out.print("File was deleted\n");
        }else {
        	System.out.print("File can't be deleted\n");
        }
    }
	
    static void append_file() throws FileNotFoundException, IOException {
        Product product;
        System.out.println( "Enter product data: " );
        try  {
        	RandomAccessFile raf = new RandomAccessFile( filename, "rw" );
            while (( product = read_product())!= null ) {
                Buffer.writeObject( raf, product );
            }
        }
        catch(Exception ex) {
        	System.out.print(ex.getMessage());
        }
    }

    static void print_file() 
            throws FileNotFoundException, IOException, ClassNotFoundException {
        try {
        	RandomAccessFile raf = new RandomAccessFile( filename, "rw" );
            long pos;
            System.out.print("store number	|product code	|product name  	|year	|storage name       	|product number	|price \n"
            		+ "-----------------------------------------------------------------------------------------------------------\n");

            while (( pos = raf.getFilePointer()) < raf.length() ) {
                Product product = (Product) Buffer.readObject( raf, pos );
                System.out.println( product );
            }
        }	
        catch(Exception ex) {
        	System.out.print(ex.getMessage());
        }
    }
}
