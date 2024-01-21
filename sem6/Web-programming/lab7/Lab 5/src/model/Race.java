package model;

import javax.persistence.*;
import java.io.Serializable;

/**
 * DAO class for Race
 */

@NamedQueries({
        @NamedQuery(name = "Race.findById",
                query = "SELECT r FROM Race r WHERE r.id=:id"),
        @NamedQuery(name = "Race.getAllRaces",
                query = "SELECT r FROM Race r"),
        @NamedQuery(name = "Race.deleteById",
                query = "DELETE FROM Race r WHERE r.id=:id"),
        @NamedQuery(name = "Race.cancelById",
                query = "UPDATE Race r SET r.status=:status WHERE r.id=:id"),
        @NamedQuery(name = "Race.updateDestinationById",
                query = "UPDATE Race r SET r.destination=:destination WHERE r.id=:id"),
        @NamedQuery(name = "Race.getDelayedRaces",
                query = "SELECT r FROM Race r WHERE r.status='Canceled'"),
        @NamedQuery(name = "Race.updateById",
                query = "UPDATE Race r SET r.capacity=:capacity," +
                        " r.brigadeId=:brigadeId," +
                        " r.status=:status," +
                        " r.destination=:destination," +
                        " r.distance=:distance," +
                        " r.planeId=:planeId" +
                        " WHERE r.id=:id")
})

@Entity
@Table(name="race")
public class Race implements Serializable {
    private static final long serialVersionUID = 1L;

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private int capacity;

    @Column(name = "brigade_id", insertable=false, updatable=false)
    private int brigadeId;

    private String status;
    private String destination;
    private int distance;

    @Column(name="plane_id", insertable = false, updatable = false)
    private int planeId;

    @ManyToOne(fetch = FetchType.EAGER, cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinColumn(name = "plane_id")
    private Plane plane;


    @ManyToOne(fetch = FetchType.EAGER, cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinColumn(name = "brigade_id")
    private Brigade brigade;

    public Plane getPlane(){
        return plane;
    }

    @Override
    public String toString() {
        return "\nRace" +
                "\n\tcapacity=" + capacity +
                "\n\tbrigadeId=" + brigadeId +
                "\n\tstatus='" + status + '\'' +
                "\n\tdestination='" + destination + '\'' +
                "\n\tdistance=" + distance +
                "\n\tplane='" + plane ;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public void setBrigadeId(int brigadeId) {
        this.brigadeId = brigadeId;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public void setDistance(int distance) {
        this.distance = distance;
    }

    public int getId() {
        return id;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getBrigadeId() {
        return brigadeId;
    }

    public String getStatus() {
        return status;
    }

    public String getDestination() {
        return destination;
    }

    public void setPlaneId(int planeId) {
        this.planeId = planeId;
    }

    public int getPlaneId() {
        return planeId;
    }

    public int getDistance() {
        return distance;
    }

    public Brigade getBrigade(){
        return brigade;
    }
}
