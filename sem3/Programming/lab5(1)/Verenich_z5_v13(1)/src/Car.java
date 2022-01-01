import java.io.Serializable;

enum CarState{
	STATE_OK,
	STATE_NOT_OK
}

enum CarStatus{
	STATUS_IS_FREE,
	STATUS_BUSY
}

public class Car implements Serializable {
	 private static final long serialVersionUID = 1L;
	 
	 private String m_mark;
	 private CarState m_state;
	 private static int m_id;
	 private CarStatus m_status = CarStatus.STATUS_IS_FREE;
	 
	 public void setStatus(CarStatus st) {
		 m_status = st;
	 }
	 public CarStatus getStatus() {
		 return m_status;
	 }
	 public String getMark() {
		 return m_mark;
	 }
	 public void setMark(String mark) throws IllegalArgumentException {
		 if(mark.length()<1) {
			 throw new IllegalArgumentException("Mark is an empty string");
		 }
		 m_mark = mark;
	 }
	 public void setState(CarState st) {
		 m_state = st;
	 }
	 public CarState getState() {
		 return m_state;
	 }
	 public int getID() {
		 return m_id;
	 }
	 
	 Car(){
		 m_mark = "Unnamed";
		 m_state = CarState.STATE_OK;
		 ++m_id;
	 }
	 Car(String mark, CarState st) throws IllegalArgumentException{
		 setMark(mark);
		 m_state = st;
		 ++m_id;
	 }
}
