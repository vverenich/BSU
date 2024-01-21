package model.dao;

import model.entity.Client;
import model.entity.Client_;

import javax.persistence.NoResultException;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.ArrayList;
import java.util.List;

/**
 * Client DAO: implementing all methods from interface
 */

public class ClientDAO extends DAO
{
    public ClientDAO()
    {
        super();
    }

    public List<Client> readClients()
    {
        List<Client> clients = new ArrayList<Client>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Client> query = cb.createQuery(Client.class);
        Root<Client> root = query.from(Client.class);
        query.select(root);

        clients = getEntityManager().createQuery(query).getResultList();

        return clients;
    }

    public Client getClientId(int id)
    {
        List<Client> clients = new ArrayList<Client>();

        CriteriaBuilder cb = getEntityManager().getCriteriaBuilder();
        CriteriaQuery<Client> query = cb.createQuery(Client.class);
        Root<Client> raceRoot = query.from(Client.class);
        query.where(cb.equal(raceRoot.get(Client_.id), id));

        clients = getEntityManager().createQuery(query).getResultList();

        return clients.get(0);
    }

}
