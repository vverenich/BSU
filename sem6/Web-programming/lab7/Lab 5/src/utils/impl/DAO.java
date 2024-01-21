package utils.impl;

import exceptions.DAOException;

import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.PersistenceContext;

/**
 * Parent class for DAO classes
 */
public class DAO {

    @PersistenceContext
    protected EntityManager em;
    public DAO(EntityManagerFactory emf) {
        em = emf.createEntityManager();
    }
    public DAO() {
    }

    /**
     * Inserts data into database
     *
     * @param entity entity
     * @return amount of inserted rows
     * @throws DAOException
     */
    void createObject(Object entity) {
        EntityManager entityManager = null;
            entityManager = em;
            entityManager.persist(entity);
    }
}
