package station;

import java.io.Serializable;

import station.Administrator;

public class Abonent  implements Serializable {
	
	private static final long serialVersionUID = 1L;
	
	public String phoneNumber;
	public int phoneBills;
	public String name;
	
	public boolean chNum;
	public boolean refSer;
	
	public Abonent(String name, String phone) {
		this.name = name;
		this.phoneNumber = phone;
		chNum = false;
		refSer = false;
	}
	
	public void wantToChangeNum() {
		chNum = true;
	}
	
	public void WantRefuseServices() {
		refSer = true;
	}
	
	public void payBills(int money) {
		phoneBills += money;
	}
	public void payBills() {
		phoneBills = 0;
	}
}
