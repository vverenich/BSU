package station;

import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.util.Locale;

import station.PhoneStation;

public class Test {
	public static void main(String[] args) {
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

			Connector con = new Connector("phone_station.dat");
			con.write( createPhoneStations());
			PhoneStation[] ps = con.read();
			System.out.println(AppLocale.getString(AppLocale.operation) + ":\t" + AppLocale.getString(AppLocale.changing_number));
			System.out.println("================================================================");
			for (int i = 0; i < 4; ++i) {
				getText(i);
				testChanging(ps, i);
				System.out.println(ps[i]);
			}
			
			System.out.println("\n\n\n\n" + AppLocale.getString(AppLocale.operation) + ":\t" + AppLocale.getString(AppLocale.provision_of_services));
			System.out.println("================================================================");
			for (int i = 4; i < ps.length; ++i) {
				getText(i);
				testRefusing(ps, i);
				System.out.println(ps[i]);
			}
			
		} catch (Exception ex) {
			System.out.println(ex.getMessage());
		}
	}
	
	public static void testChanging(PhoneStation[] ph, int i) throws Exception {
		ph[i].changeAbonNumb("+37529345983");
	}
	
	public static void testRefusing(PhoneStation[] ph, int i) throws Exception {
		ph[i].refuseSer();
	}
	
	public static PhoneStation[] createPhoneStations( ) {
		PhoneStation arr[] = new PhoneStation[8];

		for (int i = 0; i < arr.length; ++i) {
			arr[i] = new PhoneStation(
						new Administrator(AppLocale.getString(AppLocale.Kolia)), 
						new Abonent(AppLocale.getString(AppLocale.Ivan), "+375442349520"));
		}
		
		//first
		// ---
		
		//second
		arr[1].abonent.wantToChangeNum();
		
		//third
		arr[2].admin.allowChNum();
		
		//forth
		arr[3].abonent.wantToChangeNum();
		arr[3].admin.allowChNum();
		
		
		// refuse
		//fifth
		arr[4].abonent.WantRefuseServices();
		
		//sixth
		arr[5].admin.refuseServices();
		
		//seventh
		arr[6].abonent.WantRefuseServices();
		arr[6].admin.refuseServices();
		
		//eighth
		arr[7].abonent.phoneBills = -20;
		arr[7].abonent.WantRefuseServices();
		arr[7].admin.refuseServices();
		
		return arr;
	}

	public static void getText(int i) {
		switch(i) {
		case 0: {
			System.out.println("\n" + AppLocale.getString(AppLocale.first) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 1: {
			System.out.println("\n" + AppLocale.getString(AppLocale.second) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 2: {
			System.out.println("\n" + AppLocale.getString(AppLocale.third) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 3: {
			System.out.println("\n" + AppLocale.getString(AppLocale.forth) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 4: {
			System.out.println("\n" + AppLocale.getString(AppLocale.fifth) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 5: {
			System.out.println("\n" + AppLocale.getString(AppLocale.sixth) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 6: {
			System.out.println("\n" + AppLocale.getString(AppLocale.seventh) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		case 7: {
			System.out.println("\n" + AppLocale.getString(AppLocale.eighth) + " "+ AppLocale.getString(AppLocale.station) + ":");
		} break;
		}
	}
	
	

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

}
