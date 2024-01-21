package model;
import org.hibernate.annotations.LazyCollection;
import org.hibernate.annotations.LazyCollectionOption;

import javax.persistence.*;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

@NamedQueries({
        @NamedQuery(name = "Brigade.findById",
                    query = "SELECT b FROM Brigade b WHERE b.id=:id"),
        @NamedQuery(name = "Brigade.deleteById",
                    query = "DELETE FROM Brigade b WHERE b.id=:id"),
        @NamedQuery(name = "Brigade.updateById",
                    query = "UPDATE Brigade b SET b.commanderId=:id_commander WHERE b.id=:id")
})

@Entity
@Table(name = "Brigade")
public class Brigade implements Serializable {
    private static final long serialVersionUID = 1L;

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @Column(name = "id_commander")
    private int commanderId;

    @OneToMany(cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinColumn(name = "brigade_id")
    @LazyCollection(LazyCollectionOption.FALSE)
    private List<Race> races;

    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(name = "brigade_emp",
            joinColumns = @JoinColumn(name = "brigade_id", referencedColumnName = "id"),
            inverseJoinColumns = @JoinColumn(name = "emp_id", referencedColumnName = "id"))
    private List<Employee> employees;

    public void setId(int id) {
        this.id = id;
    }

    public void setCommanderId(int commanderId) {
        this.commanderId = commanderId;
    }

    public int getId() {
        return id;
    }

    public int getCommanderId() {
        return commanderId;
    }

    public void setEmployees(ArrayList<Employee> employees) {
        this.employees = employees;
    }

    public List<Employee> getEmployees() {
        return employees;
    }

    @Override
    public String toString() {
        return "Brigade{" +
                "id=" + id +
                ", commanderId=" + commanderId +
                ", employees=" + employees +
                '}';
    }
    public Brigade(){}
}
