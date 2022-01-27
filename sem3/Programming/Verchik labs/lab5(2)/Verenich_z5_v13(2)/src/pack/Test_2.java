package pack;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Locale;

public class Test_2 {
	static Locale createLocale( String[] args )	{
		if ( args.length == 2 ) {
			return new Locale( args[0], args[1] );
		} else if( args.length == 4 ) {
			return new Locale( args[2], args[3] );
		}
		return null;
	}
	
	static void setupConsole(String[] args) {
		if ( args.length >= 2 ) {
			if ( args[0].compareTo("-encoding")== 0 ) {
				try {
					System.setOut( new PrintStream( System.out, true, args[1] ));
				} catch ( UnsupportedEncodingException ex ) {
					System.err.println( "Unsupported encoding: " + args[1] );
					System.exit(1);
				}				
			}
		}
	}
	
	public static void main(String[] args) {
			MotorDepot motorDepot = new MotorDepot();
			/*
			Car car1 = new Car(new String("BMW"), CarState.STATE_OK);
			Car car2 = new Car(new String("Opel"), CarState.STATE_OK);
			Driver driver1 = new Driver(new String("Josh"),car1);
			Driver driver2 = new Driver(new String("John"), new Car("Mercedes", CarState.STATE_NOT_OK));
			
			motorDepot.m_dispatcher.createTrip(driver1, "Minsk - Moscow", TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
			motorDepot.m_dispatcher.changeDriver(driver2, motorDepot.m_trips.get(0));
			motorDepot.m_dispatcher.setCar(car2, motorDepot.m_trips.get(0));
			
			driver2.setCarState(CarState.STATE_OK);
			
			motorDepot.m_dispatcher.createTrip(driver1, "Minsk - Baranovichi", TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
			motorDepot.m_dispatcher.createTrip(new Driver("Ivan", new Car("Reno",CarState.STATE_OK)), "Minsk - Baranovichi", TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
			motorDepot.m_trips.get(2).getDriver().setTripState(TripState.STATE_DONE, motorDepot.m_trips.get(2));
			*/
			try {
				setupConsole( args );
				Locale loc = createLocale( args );
				if ( loc == null ) {
					System.err.println( 
							"Invalid argument(s)\n" +
					        "Syntax: [-encoding ENCODING_ID] language country\n" +
							"Example: -encoding Cp855 be BY" );
					System.exit(1);
				}
				AppLocale.set( loc );
				
				Car car1 = new Car(AppLocale.getString(AppLocale.bmw), CarState.STATE_OK);
				Car car2 = new Car( AppLocale.getString(AppLocale.opel) , CarState.STATE_OK);
				Driver driver1 = new Driver(AppLocale.getString(AppLocale.josh),car1);
				Driver driver2 = new Driver(AppLocale.getString(AppLocale.john), new Car(AppLocale.getString(AppLocale.mercedes), CarState.STATE_NOT_OK));
				
				motorDepot.m_dispatcher.createTrip(driver1,AppLocale.getString(AppLocale.minskMoscow), TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
				motorDepot.m_dispatcher.changeDriver(driver2, motorDepot.m_trips.get(0));
				motorDepot.m_dispatcher.setCar(car2, motorDepot.m_trips.get(0));
				
				driver2.setCarState(CarState.STATE_OK);
				
				motorDepot.m_dispatcher.createTrip(driver1, AppLocale.getString(AppLocale.minskPinsk), TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
				motorDepot.m_dispatcher.createTrip(new Driver(AppLocale.getString(AppLocale.john), new Car(AppLocale.getString(AppLocale.reno),CarState.STATE_OK)), AppLocale.getString(AppLocale.minskBrest), TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
				motorDepot.m_trips.get(2).getDriver().setTripState(TripState.STATE_DONE, motorDepot.m_trips.get(2));

				Connector con = new Connector("band.dat");
				con.write(motorDepot.m_trips);
				ArrayList<Trip> trips = con.read();
				for(Trip t: trips) {
					System.out.println(t);
					}
			}
			catch(Exception e) {
				System.out.println(e);
			}
	}
}