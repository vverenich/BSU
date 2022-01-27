package station;

import java.io.Serializable;
import java.text.DateFormat;
import java.util.Date;
import java.util.Locale;


public class PhoneStation  implements Serializable {
	
	private static final long serialVersionUID = 1L;
	
	public Administrator admin;
	public Abonent abonent;
	public String statusRefused;
	public String statusPhoneNumber;
	public String status_of_phone;
	
	public final Date creationDate = new Date();
	public String getCreationDate() {
		DateFormat dateFormatter = DateFormat.getDateTimeInstance(
				DateFormat.DEFAULT, DateFormat.DEFAULT, AppLocale.get());
	    String dateOut = dateFormatter.format(creationDate);
		return dateOut;
	}
	
	public PhoneStation(Administrator admin, Abonent abonent) {
		this.admin = admin;
		this.abonent = abonent;
		abonent.phoneBills = 100;
		this.statusRefused = AppLocale.getString(AppLocale.services_connected);
		this.statusPhoneNumber = AppLocale.getString(AppLocale.not_changed) ;
		this.status_of_phone = AppLocale.getString(AppLocale.active);
	}
	
	public void addAbon(Abonent ab) {
		abonent = ab;
	}
	public void addAdm(Administrator ad) {
		admin = ad;
	}
	
	public Administrator getAdm() {
		return admin;
	}
	public Abonent getAbon() {
		return abonent;
	}
	
	
	public void changeAbonNumb(String newNum) throws Exception {
		if (abonent == null || abonent == null)
			return;
		
		if (admin.checkBills(abonent) == false) {
			this.status_of_phone = AppLocale.getString(AppLocale.blocked);
			return;
		}
		
		if (abonent.chNum == true && admin.chNum == true) {
			abonent.phoneNumber = newNum;
			this.statusPhoneNumber = AppLocale.getString(AppLocale.changed);
		}
		if (abonent.chNum == false) {
			this.statusPhoneNumber = AppLocale.getString(AppLocale.denied_by_abonent);
		}
		if (admin.chNum == false) {
			this.statusPhoneNumber = AppLocale.getString(AppLocale.denied_by_admin);
		}
	}
	
	public void refuseSer() throws Exception {
		if (abonent == null || admin == null)
			return;
		
		if (admin.checkBills(abonent) == false) {
			this.status_of_phone = AppLocale.getString(AppLocale.blocked);
			return;
		}
		
		
		
		if (abonent.refSer == true && admin.refSer == true ) {
			this.statusRefused = AppLocale.getString(AppLocale.removed_services);
			return;
		}
		
		if (abonent.refSer == false) {
			this.statusRefused = AppLocale.getString(AppLocale.denied_by_abonent);
			return;
		}
		if (admin.refSer == false) {
			this.statusRefused = AppLocale.getString(AppLocale.denied_by_admin);
		}

	}
	
	public String toString() {
		return new String( AppLocale.getString( AppLocale.admin_name ) + ":\t\t\t\t" + admin.name + "\n" +
				           AppLocale.getString( AppLocale.abonent_name ) + ":\t\t\t" + abonent.name + "\n" + 
				           AppLocale.getString( AppLocale.phone_number) + ":\t\t\t" + abonent.phoneNumber + "\n" +
				           AppLocale.getString( AppLocale.phone_bills ) + ":\t\t" + abonent.phoneBills + "\n" +
				           AppLocale.getString( AppLocale.status_phone ) + ":\t\t" +  status_of_phone + "\n" +
				           AppLocale.getString( AppLocale.status_services ) + ":\t\t\t"  + statusRefused + "\n" +
				           AppLocale.getString( AppLocale.status_phone_number) + ":\t" + statusPhoneNumber + "\n" +
				           AppLocale.getString( AppLocale.creation ) + ":\t\t\t" + getCreationDate()
				           );
	}
	
}
