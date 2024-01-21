package model.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Set;

@Entity
@Table(name = "Room")
@NamedQueries({
        @NamedQuery(name = "Room.getAll", query = "select r from Room r where r.capacity >= :cap order by r.type, r.capacity"),
        @NamedQuery(name = "Room.getTypeRoom", query = "select r from Room r where " +
                "r.type = :ty order by r.type, r.capacity"),

        @NamedQuery(name = "Room.getNotAvailable", query = "SELECT re.roomId, bo.arrivalTime, " +
                "bo.departureTime FROM Receipt re " +
                "INNER JOIN re.bookingId bo INNER JOIN re.roomId ro " +
                "WHERE ro.capacity >= :cap AND bo.isConfirmed = 1 AND ro.type = :ty")
})

public class Room implements Serializable
{
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;

    @Column(name = "capacity")
    private int capacity;

    @Column(name = "price")
    private double price;

    @Column(name = "type")
    private String type;

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "roomId")
    private Set<Receipt> receipts;

    public Room() {}

    public void setId(int id)
    {
        this.id = id;
    }

    public void setCapacity(int capacity)
    {
        this.capacity = capacity;
    }

    public void setPrice(double price)
    {
        this.price = price;
    }

    public void setType(String type)
    {
        this.type = type;
    }

    public int getId() {
        return id;
    }

    public double getPrice()
    {
        return price;
    }

    public int getCapacity()
    {
        return capacity;
    }

    public String getType()
    {
        return type;
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
        return "\nRoom #" + id + ": " +
                "price: "  + price +
                ", capacity: " + capacity +
                ", type: " + type;
    }
}
