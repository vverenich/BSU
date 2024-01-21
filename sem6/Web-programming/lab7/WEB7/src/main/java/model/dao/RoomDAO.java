package model.dao;

import model.entity.*;

import javax.persistence.TypedQuery;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Join;
import javax.persistence.criteria.Root;
import java.sql.Date;
import java.util.ArrayList;
import java.util.List;


/**
 * Room DAO: implementing all methods from interface
 */


public class RoomDAO extends DAO
{
    public RoomDAO()
    {
        super();
    }

    public void roomListRemove(List<Room> rooms, int index)
    {
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms.get(i).getId() == index)
                rooms.remove(i);
        }
    }

    public List<Room> showAvailableRooms(int guests, Date arrivalTime, Date departureTime, String type)
    {
        List<Room> roomList = typeRooms(type);

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Object[]> query = cb.createQuery(Object[].class);

        Root<Room> roomRoot = query.from(Room.class);
        Join<Room, Receipt> receiptJoin = roomRoot.join(Room_.receipts);
        Join<Receipt, Booking> bookingJoin = receiptJoin.join(Receipt_.bookingId);

        query.where(cb.greaterThanOrEqualTo(roomRoot.get(Room_.capacity), guests),
                cb.equal(roomRoot.get(Room_.type), type),
                cb.equal(bookingJoin.get(Booking_.isConfirmed), 1));

        TypedQuery<Object[]> typedQuery = getEntityManager().createQuery(
                query.multiselect(roomRoot.get(Room_.id),
                        bookingJoin.get(Booking_.arrivalTime),
                        bookingJoin.get(Booking_.departureTime))
        );

        for (Object[] ob : typedQuery.getResultList())
        {
            int roId = (Integer)ob[0];

            if (arrivalTime.compareTo(Date.valueOf(ob[2].toString())) >= 0) {}
            else if (departureTime.compareTo(Date.valueOf(ob[1].toString())) <= 0) {}
            else
                roomListRemove(roomList, roId);
        }

        return roomList;
    }

    public List<Room> readRooms(int guests)
    {
        List<Room> rooms = new ArrayList<Room>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Room> query = cb.createQuery(Room.class);
        Root<Room> root = query.from(Room.class);
        query.where(cb.greaterThanOrEqualTo(root.get(Room_.capacity), guests));
        query.orderBy(cb.asc(root.get(Room_.type)));
        query.orderBy(cb.asc(root.get(Room_.capacity)));

        rooms = getEntityManager().createQuery(query).getResultList();

        return rooms;
    }

    public List<Room> typeRooms(String type)
    {
        List<Room> rooms = new ArrayList<Room>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Room> query = cb.createQuery(Room.class);
        Root<Room> root = query.from(Room.class);
        query.where(cb.equal(root.get(Room_.type), type));
        query.orderBy(cb.asc(root.get(Room_.capacity)));

        rooms = getEntityManager().createQuery(query).getResultList();

        return rooms;
    }
}
