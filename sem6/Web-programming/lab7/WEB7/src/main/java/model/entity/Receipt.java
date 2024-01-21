package model.entity;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "Receipt")
@NamedQueries({
        @NamedQuery(name = "Receipt.getAll", query = "select re from Receipt re"),
        @NamedQuery(name = "Receipt.getNotPaid", query = "select re from Receipt re where re.isPaid = 0"),
        @NamedQuery(name = "Receipt.getNotPaidClient", query = "select re from Receipt re  " +
                "where re.isPaid = 0 and re.clientId.id = :id"),
        @NamedQuery(name = "Receipt.getNotAvailableRooms", query =
                "SELECT re.roomId, bo.arrivalTime, " +
                        "bo.departureTime FROM Receipt re " +
                        "INNER JOIN re.bookingId bo INNER JOIN re.roomId ro " +
                        "WHERE ro.capacity >= :cap")
})
public class Receipt implements Serializable
{
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @Column(name = "is_paid")
    private int isPaid;

    @Column(name = "total")
    private double total;

    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "client_id", referencedColumnName = "id")
    private Client clientId;

    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "room_id", referencedColumnName = "id")
    private Room roomId;

    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "booking_id", referencedColumnName = "id")
    private Booking bookingId;
    
    public Receipt() {}

    public int getId() {
        return id;
    }

    public void setTotal(double total) {
        this.total = total;
    }

    public double getTotal() {
        return total;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void getTotal(double total) {
        this.total = total;
    }

    public int isPaid()
    {
        return isPaid;
    }

    public void setPaid(int paid)
    {
        this.isPaid = paid;
    }

    public Client getClientId() {
        return clientId;
    }

    public Booking getBookingId() {
        return bookingId;
    }

    public Room getRoomId() {
        return roomId;
    }

    public void setBookingId(Booking bookingId) {
        this.bookingId = bookingId;
    }

    public void setClientId(Client clientId) {
        this.clientId = clientId;
    }

    public void setRoomId(Room roomId) {
        this.roomId = roomId;
    }


    @Override
    public String toString()
    {
        return "\nReceipt #" + id + ": " +
                "is paid: "  + isPaid +
                ", total: "  + total +
                ", client id: "  + clientId.getId() +
                ", room id: " + roomId.getId() +
                ", booking id: " + bookingId.getId();
    }
}
