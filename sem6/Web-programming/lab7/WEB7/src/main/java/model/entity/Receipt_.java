package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Receipt.class)
public class Receipt_
{
    public static volatile SingularAttribute<Receipt, Integer> id;
    public static volatile SingularAttribute<Receipt, Integer> isPaid;
    public static volatile SingularAttribute<Receipt, Double> total;
    public static volatile SingularAttribute<Receipt, Client> clientId;
    public static volatile SingularAttribute<Receipt, Integer> roomId;
    public static volatile SingularAttribute<Receipt, Booking> bookingId;
}
