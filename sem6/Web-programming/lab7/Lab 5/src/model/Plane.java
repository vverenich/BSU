package model;

import javax.persistence.*;
import java.io.Serializable;
import java.util.List;

/**
 * DAO class for Plane
 */

@NamedQueries({
        @NamedQuery(name = "Plane.findById",
                query = "SELECT p FROM Plane p WHERE p.id=:id"),
        @NamedQuery(name = "Plane.deleteById",
                query = "DELETE FROM Plane p WHERE p.id=:id"),
        @NamedQuery(name = "Plane.updateById",
                query = "UPDATE Plane p SET p.number=:number, p.capacity=:capacity WHERE p.id=:id")
})

@Entity
@Table(name = "plane")
public class Plane implements Serializable {
    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @Column(name = "nmbr")
    private String number;
    private int capacity;

    @OneToMany(fetch = FetchType.EAGER, cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinColumn(name = "plane_id")
    private List<Race> races;

    public void setId(int id) {
        this.id = id;
    }

    public void setNumber(String number) {
        this.number = number;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getId() {
        return id;
    }

    public String getNumber() {
        return number;
    }

    @Override
    public String toString() {
        return "Plane{" +
                "id=" + id +
                ", number='" + number + '\'' +
                ", capacity=" + capacity +
                '}';
    }
}
