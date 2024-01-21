package model.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Set;

@Entity
@Table(name = "Client")
@NamedQueries({
        @NamedQuery(name = "Client.getAll", query = "select c from Client c"),
        @NamedQuery(name = "Client.getClientId", query = "select c from Client c where c.id = :id")
})

public class Client implements Serializable
{
    @Id
    private int id;

    @Column(name = "name")
    private String name;


    @Column(name = "password")
    private String password;

    @OneToMany(fetch = FetchType.LAZY, mappedBy = "clientId")
    private Set<Receipt> receipts;

    public Client() {}

    public void setId(int id)
    {
        this.id = id;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public void setReceipts(Set<Receipt> receipts)
    {
        this.receipts = receipts;
    }

    public int getId()
    {
        return id;
    }

    public String getName()
    {
        return name;
    }

    public Set<Receipt> getReceipts()
    {
        return receipts;
    }


    public String getPassword()
    {
        return password;
    }

    public void setPassword(String password)
    {
        this.password = password;
    }

    @Override
    public String toString()
    {
        return "\nClient #" + id + ": " + name ;
    }
}
