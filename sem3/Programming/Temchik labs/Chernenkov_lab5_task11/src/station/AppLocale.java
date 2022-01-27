package station;

import java.util.*;

public class AppLocale {
	private static final String strMsg = "Msg";
	private static Locale loc = Locale.getDefault();
	private static ResourceBundle res = 
			ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
	
	static Locale get() {
		return AppLocale.loc;
	}
	
	static void set( Locale loc ) {
		AppLocale.loc = loc;
		res = ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
	}
	
	static ResourceBundle getBundle() {
		return AppLocale.res;
	}
	
	static String getString( String key ) {
		return AppLocale.res.getString(key);
	}
	
	// Resource keys:
	
	public static final String removed_services = "removed_services";
	public static final String changing_number = "changing_number";
	public static final String denied_by_abonent="denied_by_abonent";
	public static final String denied_by_admin="denied_by_admin";
	public static final String Kolia="Kolia";
	public static final String Ivan="Ivan";
	public static final String active="active";
	public static final String blocked="blocked";
	public static final String services_connected="services_connected";
	public static final String name = "name";
	public static final String number="number";
	public static final String changed="changed";
	public static final String admin_name="admin_name";
	public static final String abonent_name="abonent_name";
	public static final String status_services="status_services";
	public static final String phone_number="phone_number";
	public static final String status_phone="status_phone";
	public static final String status_phone_number="status_phone_number";
	public static final String station="station";
	public static final String phone_bills="phone_bills";
	public static final String creation="creation";

	public static final String first="first";
	public static final String second="second";
	public static final String third="third";
	public static final String forth="forth";
	public static final String fifth="fifth";
	public static final String sixth="sixth";
	public static final String seventh="seventh";
	public static final String eighth="eighth";
	
	public static final String operation="operation";
	public static final String provision_of_services="provision_of_services";
	public static final String not_changed="not_changed";
	
	
}
