import java.util.Arrays;

public class Test {
	static void sortAndPrint(Lorry[] pl, int sortBy) {
		 	System.out.println( "----- Sorted by: " + Lorry.getSortByName(sortBy));
	        Arrays.sort( pl, Lorry.getComparator(sortBy));
	        System.out.printf( Lorry.format() );
	        System.out.println();
	        for( Lorry cnt : pl ) {
	            System.out.println( Lorry.format( cnt ) );
	        }
	}
    public static void main(String[] args) {
        try {
        	Lorry[] pl = new Lorry[3];
            pl[0] = new Lorry( "Mercedes|89|100|100" );
            pl[1] = new Lorry( "BMW|80|20|30" );
            pl[2] = new Lorry( "Toyota", "90", "100", "50" );
            sortAndPrint( pl, 0 );
            sortAndPrint( pl, 1 );
            sortAndPrint( pl, 2 );
            for(Object e: pl[0]) {
            	System.out.println(e);
            }
            // exception test:
            new Lorry("Test exception object");
        }
        catch ( Exception e ) {
            System.out.println( "Exception: " + e );
        }
    }
}
