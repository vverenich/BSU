import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;

public class Lorry  extends  Car implements Comparable<Lorry>, Iterable<String>, Iterator<String>{
	//********************************************************
	//adding field and methods for it
	private int m_liftingCapacity;
	
	int getLiftingCapacity() {
		return m_liftingCapacity;
	}
	
	void setLiftingCapacity(int cap) {
		m_liftingCapacity = cap;
	}
	//********************************************************
	
	public static  String[] names= {
			"Mark",
			"Cylinder Number",
			"Power",
			"Lifting capacity"
	};
	   public static String[] formatStr =  {
		    	"%-9s",   // 
		    	"%-9s",   //
		    	"%-9s",   //
		    	"%-9s"
		    };
	   
	 //********************************************************
	    // sort
	    public static String getSortByName(int sortBy) {
	    	return Lorry.names[sortBy];
	    }
	    
	    public static Comparator<Lorry> getComparator(int sortBy) {
	        if ( sortBy >= names.length || sortBy < 0 ) {
	            throw new IndexOutOfBoundsException();
	        }
	    	return new Comparator<Lorry> () {
				@Override
				public int compare(Lorry c0, Lorry c1) {
			        return c0.fields[sortBy].compareTo( c1.fields[sortBy]);
				}
	    	};
	    }

	//********************************************************
	//checkers for fields
	
	protected boolean validStringMember(String str) {
		return str != null && str.length()>0;
	}
	
	protected boolean validIntMember(String str) {
		if(Integer.parseInt(str)>=0) {
			return true;
		}
		return false;
	}
	//********************************************************
	//Fields of class and their methods(BEGIN)
	
	private String[] fields = new String[4];
	
	public int length() {
		return fields.length;
	}
	
	public String getField(int idx) {
		if(idx>=length() || idx <0) {
			throw new IndexOutOfBoundsException();
		}
		return fields[idx];
	}
	
	public void setField(int idx, String value) throws ArgException{
		if ( idx >= length() || idx < 0 ) {
            throw new IndexOutOfBoundsException();
        } 
		if (( idx == 0 && validStringMember( value )== false ) 				||
                ( idx == 1 && validIntMember( value )== false ) 			||
                ( idx > 1 && idx < 4 && validIntMember( value )== false ) 	||
                ( idx == 4 && validIntMember( value )== false ))			 {
                throw new ArgException( value );
            }
            fields[idx] = value;
	}
	
	//********************************************************
	//Iterable<String>, Iterator<String>
	public Iterator<String> iterator(){
		reset();
		return this;
	}
	
	private int iterator_idx=0;
	
	public void reset() {
		iterator_idx = 0; 
	}
	
	public boolean hasNext() {
		return iterator_idx >= fields.length?false: true;
	}
	
	public void remove() {
		//
	}
	
	public String next() {
		if(iterator_idx<fields.length) {
			return fields[iterator_idx++];
		}
		reset();
		return null;
	}
	//********************************************************
	//Comparable<Lorry>
	
	public int compareTo(Lorry l) {
		return fields[0].compareTo(l.fields[0]);
	}
	//********************************************************
	//toString
	public String toString() {
		if(fields == null) {
			return "| | | "; 
		}
		return "Mark: "+fields[0]+" Cylinder Number: " + fields[1]+
			 		" Power: "+ fields[2]+" Lifting Capacity: "+fields[3];
	}
	//********************************************************
	//constructors:
	//public Lorry() {}
	private void setup(String[] args) throws ArgException{
		if(args == null) {
			throw new ArgException("null pointer passed for args");
		}
		if(args.length<2 || args.length > names.length) {
			throw new ArgException(Arrays.toString(args));
		}
		fields= new String[names.length];
		int i =0;
		for(; i<args.length; ++i) {
			setField(i, args[i]);
		}
		while(i<names.length) {
			fields[++i] = "";
		}
	}
	public Lorry(String str) throws ArgException{
		if(str ==null) {
			throw new ArgException("null pointer passed for str");
		}
		// count tokens:
		int num =1, idx =0, idxFrom =0;
		while((idx =str.indexOf('|', idxFrom))!=-1) {
			idxFrom = idx +1;
			++num;
		}
		// allocate array
		String[] args =new String[num];
		// put all tokens to array
		idx = 0; idxFrom = 0; num = 0;
		while (( idx = str.indexOf( '|', idxFrom ))!= -1 )
        {
        	args[num++] = str.substring( idxFrom, idx );
            idxFrom = idx + 1;
        }
		args[num]=str.substring(idxFrom);
		setup(args);
	}
	
	public Lorry( String...args ) throws ArgException {
    	setup( args );
    }
	//********************************************************
	//Formatting methods
	private static String format( Iterable<String> what ) {
    	String result = "";
    	int idx = 0;
        for( String str : what ) {
       		result += String.format( formatStr[idx++], str );
        }    	
        return result;
    }
	
	 public static String format() {
	    	return Lorry.format( Arrays.asList(Lorry.names ));
	    }
	    
	    public static String format(Lorry l ) {
	    	return Lorry.format(((Iterable<String>) l ));
	    }
	  //*******************************************************
	public static class ArgException extends Exception {
		private static final long serialVersionUID = 1L;

		ArgException( String arg ) {
			super( "Invalid argument: " + arg ); 
		}
	}
}
