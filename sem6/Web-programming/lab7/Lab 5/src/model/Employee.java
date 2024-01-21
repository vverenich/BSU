package model;
import javax.persistence.*;
import java.io.Serializable;
import java.util.List;

/**
 * class for Brigade entity
 */
@NamedQueries({
        @NamedQuery(name = "Employee.findById",
                query = "SELECT e FROM Employee e WHERE e.id=:id"),
        @NamedQuery(name = "Employee.deleteById",
                query = "DELETE FROM Employee e WHERE e.id=:id"),
        @NamedQuery(name = "Employee.updateById",
                query = "UPDATE Employee e SET e.name=:name, e.position=:position WHERE e.id=:id")
})

@Entity
@Table(name = "emp")
public class Employee  implements Serializable {
    private static final long serialVersionUID = 1L;

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    private String name;
    private String position;

    @Override
    public String toString() {
        return "\nEmployee" +
                "\n\tname='" + name + '\'' +
                "\n\tposition='" + position + '\'';
    }

    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(name = "brigade_emp",
            joinColumns = @JoinColumn(name = "emp_id", referencedColumnName = "id"),
            inverseJoinColumns = @JoinColumn(name = "brigade_id", referencedColumnName = "id"))
    private List<Brigade> brigades;

    public void setId(int id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getPosition() {
        return position;
    }

    public Employee(String name, String position){
        setName(name);
        setPosition(position);
    }

    public Employee(){}
}
