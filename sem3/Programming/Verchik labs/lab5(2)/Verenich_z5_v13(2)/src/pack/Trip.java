package pack;
import java.io.Serializable;
import java.text.DateFormat;
import java.util.Date;

enum TripState{
	STATE_DONE,
	STATE_IN_PROGRESS
}

public class Trip implements Serializable {
	private static final long serialVersionUID = 1L;
	
	public final Date creationDate = new Date();
	public String getCreationDate() {
		DateFormat dateFormatter = DateFormat.getDateTimeInstance(
				DateFormat.DEFAULT, DateFormat.DEFAULT, AppLocale.get());
	    String dateOut = dateFormatter.format(creationDate);
		return dateOut;
	}
	
	private Driver m_driver;
	private String m_route;
	private TripState m_state;
	
	public void setDriver(Driver driver) {
		if(driver.getStatus() == DriverStatus.STATUS_BUSY) {
			throw new IllegalArgumentException("This driver is already busy");
		}
		if(m_driver!=null) {
			m_driver.setStatus(DriverStatus.STATUS_IS_FREE);
		}
		m_driver = driver;
		m_driver.setStatus(DriverStatus.STATUS_BUSY);
		
	}
	public Driver getDriver() {
		return m_driver;
	}
	public void setRoute(String route)  throws IllegalArgumentException {
		if(route.length()<1) {
			throw new IllegalArgumentException("Route is an empty string");
		}
		m_route = route;
	}
	public String getRoute() {
		return m_route;
	}
	public void setTripState(TripState state) {
		m_state = state;
	}
	public TripState getTripState() {
		return m_state;
	}
	
	Trip(Driver driver, String route, TripState state) throws IllegalArgumentException {
		setDriver(driver);
		setRoute(route);
		m_state = state;
	}
	public String toString() {
		String stateOfCar;
		stateOfCar  = m_driver.getCar().getState()==CarState.STATE_OK?"is OK":"is not OK";
		String stateOfTrip;
		stateOfTrip = m_state==TripState.STATE_DONE?"COMPLETED":"IN PROGRESS";
		return new String( AppLocale.getString(AppLocale.driver) + ": "+m_driver.getName()+"\t| " +
				AppLocale.getString(AppLocale.car)+": "+m_driver.getCar().getMark()+"\t| "+
				AppLocale.getString(AppLocale.numberOfCar)+": "+m_driver.getCar().getID() + "\t| "+
				AppLocale.getString(AppLocale.stateOfCar)+": "+stateOfCar+"\t| "+
				AppLocale.getString(AppLocale.route)+": "+m_route+"\t| "+
				AppLocale.getString(AppLocale.stateOfTrip)+": "+stateOfTrip+"\t| "+
				AppLocale.getString(AppLocale.creationDate)+": "+ getCreationDate() + " | ");
	}
}