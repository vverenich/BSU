package pack;
import java.util.ArrayList;

public class MotorDepot {
	public ArrayList<Trip> m_trips;
	public Dispatcher m_dispatcher;

	public MotorDepot() {
		m_trips = new ArrayList<Trip>();
		m_dispatcher = new Dispatcher();
	}
}