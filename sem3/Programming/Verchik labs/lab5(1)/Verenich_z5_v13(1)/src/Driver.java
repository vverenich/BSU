import java.io.Serializable;
enum DriverStatus{
	STATUS_IS_FREE,
	STATUS_BUSY
}

public class Driver implements Serializable {
	private static final long serialVersionUID = 1L;
	
	private String m_name;
	private static int m_id;
	private Car m_car;
	private DriverStatus m_status = DriverStatus.STATUS_IS_FREE;
	
	public void setStatus(DriverStatus st) {
		m_status = st;
	}
	public DriverStatus getStatus() {
		return m_status;
	}
	public String getName() {
		return m_name;
	}
	public void setName(String name) throws IllegalArgumentException {
		if(name.length()<1) {
			throw new IllegalArgumentException("Name is an empty string");
		}
		m_name = name;
	}
	public int getID() {
		return m_id;
	}
	public Car getCar() {
		return m_car;
	}
	public void setCar(Car car) throws IllegalArgumentException{
		if(car.getStatus()==CarStatus.STATUS_BUSY) {
			throw new IllegalArgumentException("This car is busy");
		}
		m_car = car;
	}
	
	Driver(){
		m_name = "Vlad";
		++m_id;
	}
	Driver(String name, Car car) throws IllegalArgumentException{
		setName(name);
		m_car = car;
	}
	
	public void setCarState(CarState st) {
		m_car.setState(st);
	}
	public void setTripState(TripState st, Trip trip) {
		if(trip.getDriver().getID()!=m_id) {
			throw new IllegalArgumentException("This trip doesn't belong to this driver");
		}
		if(st == TripState.STATE_DONE) {
			trip.getDriver().setStatus(DriverStatus.STATUS_IS_FREE);
		}
		trip.setTripState(st);
	}
}
