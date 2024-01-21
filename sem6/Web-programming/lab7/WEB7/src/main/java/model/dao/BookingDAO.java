package model.dao;

import model.entity.Booking;
import model.entity.Booking_;
import model.entity.Client;
import model.entity.Client_;

import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.sql.Date;
import java.util.ArrayList;
import java.util.List;

public class BookingDAO extends DAO
{
    public BookingDAO()
    {
        super();
    }

    public List<Booking> printBookings()
    {
        List<Booking> bookings = new ArrayList<Booking>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Booking> query = cb.createQuery(Booking.class);
        Root<Booking> root = query.from(Booking.class);
        query.where(cb.equal(root.get(Booking_.isConfirmed), 0));

        bookings = getEntityManager().createQuery(query).getResultList();

        return bookings;
    }

    public void createBooking(String type, int guests, Date arrivalTime,
                              Date departureTime, int clientId, int isConfirmed)
    {
        try
        {
            Client client;
            CriteriaBuilder clientBuilder = getEntityManager().getCriteriaBuilder();
            CriteriaQuery<Client> clientQuery = clientBuilder.createQuery(Client.class);
            Root<Client> clientRoot = clientQuery.from(Client.class);
            clientQuery.where(clientBuilder.equal(clientRoot.get(Client_.id), clientId));

            client = getEntityManager().createQuery(clientQuery).getSingleResult();

            getEntityManager().getTransaction().begin();

            Booking booking = new Booking();
            booking.setType(type);
            booking.setGuests(guests);
            booking.setArrivalTime(arrivalTime);
            booking.setDepartureTime(departureTime);
            booking.setClientId(client);
            booking.setIsConfirmed(isConfirmed);

            getEntityManager().persist(booking);
            getEntityManager().getTransaction().commit();


            System.out.println("Successful insert");
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }

}
