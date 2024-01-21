package model.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.sql.Date;
import java.util.Set;

@Entity
@Table(name = "Booking")
@NamedQuery(name = "Booking.getNewBooking", query = "select bo from Booking bo where bo.isConfirmed = 0")

public class Booking implements Serializable
{
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @Column(name = "type")
    private String type;

    @Column(name = "guests")
    private int guests;

    @Column(name = "arrival_time")
    private Date arrivalTime;

    @Column(name = "departure_time")
    private Date departureTime;

    @ManyToOne(cascade = CascadeType.ALL)
    @JoinColumn(name = "client_id", referencedColumnName = "id")
    private Client clientId;

    @Column(name = "is_confirmed")
    private int isConfirmed;

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "bookingId")
    private Set<Receipt> receipts;

    public String getType() {
        return type;
    }

    public int getId() {
        return id;
    }

    public Date getArrivalTime() {
        return arrivalTime;
    }

    public Date getDepartureTime() {
        return departureTime;
    }

    public int getGuests() {
        return guests;
    }

    public Client getClientId() {
        return clientId;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setGuests(int guests) {
        this.guests = guests;
    }

    public void setArrivalTime(Date arrivalTime) {
        this.arrivalTime = arrivalTime;
    }

    public void setDepartureTime(Date departureTime) {
        this.departureTime = departureTime;
    }

    public void setClientId(Client client)
    {
        this.clientId = client;
    }

    public int getIsConfirmed() {
        return isConfirmed;
    }

    public void setIsConfirmed(int isConfirmed) {
        this.isConfirmed = isConfirmed;
    }

    public Set<Receipt> getReceipts()
    {
        return receipts;
    }

    public void setReceipts(Set<Receipt> receipts)
    {
        this.receipts = receipts;
    }

    @Override
    public String toString()
    {
        String status = "";
        if (isConfirmed == 0)
            status = "not yet confirmed";
        else if (isConfirmed == 1)
            status = "accepted";
        else if (isConfirmed == -1)
            status = "declined";

        return "\nBooking #" + id + ": " +
                "type: "  + type +
                ", guest(s): " + guests +
                ", arrival time: " + arrivalTime +
                ", departure time: " + departureTime +
                ", client id: " + clientId.getId() +
                ", confirmation status: " + status;
    }
}
