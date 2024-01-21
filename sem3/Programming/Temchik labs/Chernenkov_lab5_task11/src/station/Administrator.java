package station;

import java.io.Serializable;

import station.Abonent;

public class Administrator implements Serializable {
	
	private static final long serialVersionUID = 1L;
	
	public String name;
	public boolean chNum;
	public boolean refSer;
	
	public Administrator(String name) {
		this.name = name;
		chNum = false;
		refSer = false;
	}
	
	public void allowChNum() {
		chNum = true;
	}
	
	public void refuseServices() {
		refSer = true;
	}
	
	public boolean checkBills(Abonent abon) {
		if (abon == null) {
			return true;
		}
		if (abon.phoneBills >= 0) {
			return true;
		}
		return false;
	}
}
