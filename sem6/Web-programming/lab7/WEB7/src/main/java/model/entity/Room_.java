package model.entity;

import javax.persistence.metamodel.SetAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Room.class)
public class Room_
{
    public static volatile SingularAttribute<Room, Integer> id;
    public static volatile SingularAttribute<Room, Integer> capacity;
    public static volatile SingularAttribute<Room, Double> price;
    public static volatile SingularAttribute<Room, String> type;
    public static volatile SetAttribute<Room, Receipt> receipts;
}
