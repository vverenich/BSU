package model.dao;

import model.entity.*;

import javax.persistence.TypedQuery;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Join;
import javax.persistence.criteria.Root;
import java.sql.Date;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.List;

/**
 * Receipt DAO: implementing all methods from interface
 */

public class ReceiptDAO extends DAO
{
    public List<Room> roomList = new ArrayList<Room>();
    public Booking item;

    public ReceiptDAO()
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

    public double roomListPrice (List<Room> rooms, int index)
    {
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms.get(i).getId() == index)
                return rooms.get(i).getPrice();
        }
        return 0;
    }

    public Receipt receiptListItem (List<Receipt> receipts, int index)
    {
        for (int i = 0; i < receipts.size(); i++)
        {
            if (receipts.get(i).getId() == index)
                return receipts.get(i);
        }
        return null;
    }

    public Room roomListItem (List<Room> rooms, int index)
    {
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms.get(i).getId() == index)
                return rooms.get(i);
        }
        return null;
    }

    public List<Booking> confirmBookingList()
    {
        List<Booking> bookingList;

        CriteriaBuilder bookingBuilder = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Booking> bookingQuery = bookingBuilder.createQuery(Booking.class);
        Root<Booking> root = bookingQuery.from(Booking.class);
        bookingQuery.where(bookingBuilder.equal(root.get(Booking_.isConfirmed), 0));

        bookingList = getEntityManager().createQuery(bookingQuery).getResultList();

        return bookingList;
    }

    public List<Room> confirmBookingRooms(List<Booking> bookingList, int index)
    {
        for (int i = 0; i < bookingList.size(); i++)
        {
            if (bookingList.get(i).getId() == index)
            {
                item = bookingList.get(i);
                break;
            }
        }

        CriteriaBuilder roomCb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Room> roomQuery = roomCb.createQuery(Room.class);
        Root<Room> listRoot = roomQuery.from(Room.class);
        roomQuery.where(roomCb.greaterThanOrEqualTo(listRoot.get(Room_.capacity), item.getGuests()));
        roomQuery.orderBy(roomCb.asc(listRoot.get(Room_.type)));
        roomQuery.orderBy(roomCb.asc(listRoot.get(Room_.capacity)));

        roomList = getEntityManager().createQuery(roomQuery).getResultList();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Object[]> query = cb.createQuery(Object[].class);

        Root<Room> roomRoot = query.from(Room.class);
        Join<Room, Receipt> receiptJoin = roomRoot.join(Room_.receipts);
        Join<Receipt, Booking> bookingJoin = receiptJoin.join(Receipt_.bookingId);

        query.where(cb.greaterThanOrEqualTo(roomRoot.get(Room_.capacity), item.getGuests()));

        TypedQuery<Object[]> typedQuery = getEntityManager().createQuery(
                query.multiselect(roomRoot.get(Room_.id),
                        bookingJoin.get(Booking_.arrivalTime),
                        bookingJoin.get(Booking_.departureTime))
        );

        System.out.println(typedQuery.getResultList());

        for (Object[] ob : typedQuery.getResultList())
        {
            int roId = (Integer)ob[0];
            System.out.println(roId);

            if (item.getArrivalTime().compareTo(Date.valueOf(ob[2].toString())) >= 0) {}
            else if (item.getDepartureTime().compareTo(Date.valueOf(ob[1].toString())) <= 0) {}
            else
                roomListRemove(roomList, roId);
        }

        return roomList;
    }

    public Integer getDuration(Booking item)
    {
        int days = (int) ChronoUnit.DAYS.between(LocalDate.parse(item.getArrivalTime().toString()),
                LocalDate.parse(item.getDepartureTime().toString()));

        return days;
    }


    public double createBookingFinale(int mode, int roomIndex)
    {
        if (mode == 0)
        {

            System.out.println("No suitable rooms :( Booking cancelled");
            getEntityManager().getTransaction().begin();

            item.setIsConfirmed(-1);
            getEntityManager().merge(item);
            getEntityManager().getTransaction().commit();

            return 0;
        }
        else
        {
            getEntityManager().getTransaction().begin();

            item.setIsConfirmed(1);
            getEntityManager().merge(item);

            double totalPrice = getDuration(item) * roomListPrice(roomList, roomIndex);
            Receipt receipt = new Receipt();
            receipt.setPaid(0);
            receipt.setTotal(totalPrice);
            receipt.setBookingId(item);
            receipt.setClientId(item.getClientId());
            receipt.setRoomId(roomListItem(roomList, roomIndex));

            getEntityManager().persist(receipt);
            getEntityManager().getTransaction().commit();


            System.out.println("Successful update!");
            System.out.println("Client #" + item.getClientId() +
                    " receives a receipt with total amount of " + totalPrice);

            return totalPrice;
        }
    }

    public List<Receipt> readReceipts()
    {
        List<Receipt> receipts = new ArrayList<Receipt>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Receipt> query = cb.createQuery(Receipt.class);
        Root<Receipt> root = query.from(Receipt.class);
        query.select(root);

        receipts = getEntityManager().createQuery(query).getResultList();

        return receipts;
    }

    public List<Receipt> getNotPaidReceipts()
    {
        List<Receipt> receipts = new ArrayList<Receipt>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Receipt> query = cb.createQuery(Receipt.class);
        Root<Receipt> root = query.from(Receipt.class);
        query.where(cb.equal(root.get(Receipt_.isPaid), 0));

        receipts = getEntityManager().createQuery(query).getResultList();

        return receipts;
    }

    public List<Receipt> payReceiptList(int clientId)
    {
        List<Receipt> receipts = new ArrayList<Receipt>();

        Client client;
        CriteriaBuilder clientBuilder = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Client> clientQuery = clientBuilder.createQuery(Client.class);
        Root<Client> clientRoot = clientQuery.from(Client.class);
        clientQuery.where(clientBuilder.equal(clientRoot.get(Client_.id), clientId));

        client = getEntityManager().createQuery(clientQuery).getSingleResult();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Receipt> query = cb.createQuery(Receipt.class);
        Root<Receipt> root = query.from(Receipt.class);
        query.where(cb.equal(root.get(Receipt_.isPaid), 0),
                cb.equal(root.get(Receipt_.clientId), client));

        receipts = getEntityManager().createQuery(query).getResultList();

        return receipts;

    }
    public void payReceiptCheck(List<Receipt> receipts, int index)
    {
        Receipt re = receiptListItem(receipts, index);
        getEntityManager().getTransaction().begin();

        re.setPaid(1);
        getEntityManager().merge(re);
        getEntityManager().getTransaction().commit();


        System.out.println("Yaaas update");
    }
}

