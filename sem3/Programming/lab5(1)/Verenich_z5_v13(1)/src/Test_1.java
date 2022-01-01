import java.util.ArrayList;

public class Test_1 {
	public static void main(String[] args) {
		MotorDepot motorDepot = new MotorDepot();
		
		Car car1 = new Car(new String("BMW"), CarState.STATE_OK);
		Car car2 = new Car(new String("Opel"), CarState.STATE_OK);
		Driver driver1 = new Driver(new String("Josh"),car1);
		Driver driver2 = new Driver(new String("John"), new Car("Mercedes", CarState.STATE_NOT_OK));
		
		motorDepot.m_dispatcher.createTrip(driver1, "Minsk - Moscow", TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
		motorDepot.m_dispatcher.changeDriver(driver2, motorDepot.m_trips.get(0));
		motorDepot.m_dispatcher.setCar(car2, motorDepot.m_trips.get(0));
		
		driver2.setCarState(CarState.STATE_OK);
		
		motorDepot.m_dispatcher.createTrip(driver1, "Minsk - Baranovichi", TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
		motorDepot.m_dispatcher.createTrip(new Driver("Ivan", new Car("Reno",CarState.STATE_OK)), "Minsk - Brest", TripState.STATE_IN_PROGRESS, motorDepot.m_trips);
		motorDepot.m_trips.get(2).getDriver().setTripState(TripState.STATE_DONE, motorDepot.m_trips.get(2));
		
		try {
			Connector con = new Connector("trips.dat");
			con.write(motorDepot.m_trips);
			ArrayList<Trip> trips = con.read();
			for(Trip t: trips) {
				System.out.println(t);
			}
		}
		catch(Exception e) {
			System.out.println(e);
		}
	}
}
