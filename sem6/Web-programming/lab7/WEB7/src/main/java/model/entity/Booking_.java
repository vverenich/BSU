package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import java.sql.Date;

@StaticMetamodel(Booking.class)
public class Booking_
{
    public static volatile SingularAttribute<Booking, Integer> id;
    public static volatile SingularAttribute<Booking, String> type;
    public static volatile SingularAttribute<Booking, Integer> guests;
    public static volatile SingularAttribute<Booking, Date> arrivalTime;
    public static volatile SingularAttribute<Booking, Date> departureTime;
    public static volatile SingularAttribute<Booking, Client> clientId;
    public static volatile SingularAttribute<Booking, Integer> isConfirmed;
}
