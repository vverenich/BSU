package lab4_var10_Chernenkov;

import java.util.*;

public class Angle implements 
					Comparable<Angle>, Comparator<Angle>,
					Iterable<Double>, Iterator<Double> 
{
	public static class ArgException extends Exception {
		private static final long serialVersionUID = 1L;

		ArgException( String arg ) {
			super( "Invalid argument: " + arg ); 
		}
	}
	
	/////////////////////////////////////////
	// areas container
	private double[] areas = null;
    
	///////////////////////////////////////////////////
    // area names

    public static final String[] names = {
      "Angle"
    };
    
    //format strings for area printout
    public static String[] formatStr =  {
    	"%-9s",   //
    };
    
    
    // toString
    public String toString() {
        if ( areas == null ) {
            return " | | | | | | ";
        }
        
        String res = "    " + String.valueOf(String.format("%.2f'", areas[0]));
        res += "\t|    " + String.valueOf(String.format("%.2f®", GetDegrees()));
        res += "\t |    " + String.valueOf(String.format("%.4f", GetRadians()));

        return res;
    }
    // constructors:
    //public Angle() {}
    private void setup( String[] args ) throws ArgException {
    	if ( args == null ) {
    		throw new ArgException( "null pointer passed for args" );
    	}
        if ( args.length < 1 || args.length > names.length ) {
            throw new ArgException( Arrays.toString( args ));
        }
        areas = new double[names.length];
        int i = 0;
        for (; i < args.length; i++ ) {
            setArea( i, Double.parseDouble(args[i]) );
        }
        while ( i < names.length ) {
            areas[i++] = Double.NaN;
        }
    }
    
    
    public Angle( String str ) throws ArgException {
    	if ( str == null ) {
    		throw new ArgException( "null pointer passed for str" );
    	}
    	// count tokens:
    	int num = 1, idx = 0, idxFrom = 0;
        while (( idx = str.indexOf( '|', idxFrom ))!= -1 )
        {
            idxFrom = idx + 1;
            num++;
        }
        // allocate array
        String[] args = new String[num];   	
        // put all tokens to array
        idx = 0; idxFrom = 0; num = 0;
        while (( idx = str.indexOf( '|', idxFrom ))!= -1 )
        {
        	args[num++] = str.substring( idxFrom, idx );
            idxFrom = idx + 1;
        }
        args[num] = str.substring( idxFrom );
        setup( args );
    }
    
    public Angle(Angle ang) {
    	areas = new double[1];
    	areas[0] = ang.getArea(0);
    }
    
    public Angle (double angle) {
    	areas = new double[1];
    	areas[0] = angle;
    }
    
    
    ///////////////////////////////////////////////////
    // sort
    public static String getSortByName(int sortBy) {
    	if (sortBy > names.length || sortBy < 0)
            throw new IndexOutOfBoundsException();
    	return Angle.names[sortBy];
    }
    
    public static Comparator<Angle> getComparator(int sortBy) {
        if ( sortBy >= names.length || sortBy < 0 ) {
            throw new IndexOutOfBoundsException();
        }
    	return new Comparator<Angle> () {
			@Override
			public int compare(Angle left, Angle right) {
				if (Math.abs(left.areas[0] - right.areas[0]) < 1e-5)
					return 0;
				else if (left.areas[0] > right.areas[0])
					return 1;
				else
					return -1;
			}
    	};
    }
    
    public int compare(Angle left, Angle right) {
		if (Math.abs(left.areas[0] - right.areas[0]) < 1e-5)
			return 0;
		else if (left.areas[0] > right.areas[0])
			return 1;
		else
			return -1;
    }
    
    public int compareTo(Angle angle) {
    	if (Math.abs(areas[0] - angle.areas[0]) < 1e-5)
			return 0;
		else if (areas[0] > angle.areas[0])
			return 1;
		else
			return -1;
    }
    ///////////////////////////////////////////////////
    //  checkers (stubs)
	protected boolean validAngle(String str) {
		return str != null && str.length() > 0;
	}

    // indexator:
    public int length() {
    	return areas.length;    
    }
    
    public double getArea( int idx ) {
        if ( idx >= length() || idx < 0 ) {
            throw new IndexOutOfBoundsException();
        }
        return areas[idx];
    }
    
    public void setArea( int idx, double value ) throws ArgException {
        if ( idx >= length() || idx < 0 ) {
            throw new IndexOutOfBoundsException();
        }
        areas[idx] = value;
    }

    //Iterable<String>, Iterator<String>
    public Iterator<Double> iterator() {
    	reset();
        return this;
    }
    private int iterator_idx = 0;
    
    public void reset() {
        iterator_idx = 0;
    }
    public boolean hasNext() {
          return iterator_idx <  areas.length;
    }
    
    public Double next() {
    	if (hasNext()) {
    		return areas[iterator_idx++];
        }
        reset();
        return Double.NaN;
    }
    
    
       // Метод возвращает число в градусах.
    public double GetDegrees() {
        double degrees = areas[0] / 60.0 % 360; // Приводим к диапозону от -360 до 360.
        return degrees < 0 ? 360.0 + degrees : degrees; // Приводим градусы к диапазону 0-360.
    }
 
    // Метод возвращает число в радианах.
    public double GetRadians()
    {
        return GetDegrees() * Math.PI / 180.0; // Приводим градусы в радианы.
    }
 
    // Метод получения синуса угла.
    public double GetSinus() {
        return Math.sin(GetRadians());
    }
 
    // Даем возможность суммировать углы. (К примеру a = b + c, где a, b, c - переменные типа Angle)
    public static Angle sum(Angle left, Angle right) {
        return new Angle(left.areas[0] + right.areas[0]);
    }
 
    // Даем возможность вычитать углы. (К примеру: a = b - c, где a, b, c - переменные типа Angle)
    public static Angle sub(Angle left, Angle right) {
        return new Angle(left.areas[0] - right.areas[0]);
    }
 
    public static Angle mult(Angle left, Angle right) {
    	return new Angle((left.areas[0] * right.areas[0]));
    }
    
    public static Angle div(Angle left, Angle right) {
    	return new Angle(left.areas[0] / right.areas[0]);
    }

}
