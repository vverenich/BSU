
public class Car {
	private String m_mark;
	private int m_cylinderNumber;
	private int m_power;
	
	Car(){
		m_mark = null;
		m_cylinderNumber = 0;
		m_power = 0;
	}
	Car(String mark, int num, int power){
		m_mark = mark;
		m_cylinderNumber = num;
		m_power = power;
	}
	
	public void setPower(int p) {
		m_power = p;
	}
	
	public int getPower() {
		return m_power;
	}
	
	public void setMark(String str) {
		m_mark = str;
	}
	
	public String getMark() {
		return m_mark;
	}
	
	public void setNumber(int num) {
		m_cylinderNumber = num;
	}
	
	public int getNumber() {
		return m_cylinderNumber;
	}
}
