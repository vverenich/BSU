package pack;
import java.io.*;
import java.util.ArrayList;

public class Connector {
	 private String filename;

	 Connector( String filename ) {
	     this.filename = filename;
	 }
	 void write( ArrayList<Trip> trips) throws IOException {
	        FileOutputStream fos = new FileOutputStream (filename);
	        try ( ObjectOutputStream oos = new ObjectOutputStream( fos )) {
	            oos.writeInt( trips.size() );
	            for (Trip trip : trips) {
	                oos.writeObject(trip);
	            }
	            oos.flush();
	        }
	    }
	 ArrayList<Trip> read() throws IOException, ClassNotFoundException {
	        FileInputStream fis = new FileInputStream(filename);
	        try ( ObjectInputStream oin = new ObjectInputStream(fis)) {
	            int length = oin.readInt();
	            ArrayList<Trip> result = new ArrayList<Trip>();
	            for ( int i = 0; i < length; i++ ) {
	                result.add((Trip) oin.readObject());
	            }
	            return result;
	        }
	    }
}