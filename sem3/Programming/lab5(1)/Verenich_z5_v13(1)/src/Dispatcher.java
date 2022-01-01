import java.io.Serializable;
import java.util.ArrayList;

public class Dispatcher implements Serializable{
	private static final long serialVersionUID = 1L;
	
	public void createTrip(Driver driver, String route, TripState state, ArrayList<Trip> trips){
		trips.add(new Trip(driver, route, state));
	}
	public void changeDriver(Driver driver, Trip trip) {
		trip.setDriver(driver);
	}
	public void setCar(Car car, Trip trip) {
		trip.getDriver().setCar(car);
	}
}
