package model.dao;

import model.entity.Abiturient;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;

import org.hibernate.proxy.AbstractLazyInitializer;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DAOAbiturient extends DAO {
    /**
     * Constructor
     * @throws DAOException exception
     */
    public DAOAbiturient(){
        super();
    }


    /**
     * Method returns list of abiturients of faculty
     * @param id faculty id
     * @return list of abiturients of faculty
     * @throws DAOException exception
     */
    public List<Abiturient> getAbiturientsOfFaculty(int id){
        EntityManager entityManager = null;
        List<Abiturient> abiturientList;
        try {

            entityManager = getEntityManagerFactory().createEntityManager();

            abiturientList = entityManager.createNamedQuery("getAbiturientsOfFaculty", Abiturient.class)
                    .setParameter("id", id).getResultList();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return abiturientList;
    }

    /**
     * Method returns list abiturients with avg more than avg of faculty
     * @param id faculty id
     * @return abiturients with avg more than avg of faculty
     * @throws DAOException exception
     */
    public List<Abiturient> getAbiturientsWithAvgMoreThanAvgOfFaculty(int id){
        EntityManager entityManager = null;
        List<Abiturient> abiturientList;
        try {

            entityManager = getEntityManagerFactory().createEntityManager();

            abiturientList = entityManager.createNamedQuery("getAbiturientsWithAvgMoreThanAvgOfFaculty", Abiturient.class)
                    .setParameter("id", id).getResultList();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return abiturientList;
    }

    /**
     * Update number of instances in table books when reader take book
     * @param book_id book id
     * @throws DAOException exception
     */
    public void registerNewAbiturient(String surname, String first_name, String middle_name, int faculty_id) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            entityManager.getTransaction();

            entityManager.createNamedQuery("registerNewAbiturient", Abiturient.class)
            .setParameter(1, surname).setParameter(2, first_name)
            .setParameter(3, middle_name).setParameter(4, faculty_id);
            /* 
            Book book = entityManager.find(Book.class, book_id);

            transaction.begin();
            book.setNumber_of_instance(book.getNumber_of_instance() - 1);
            transaction.commit();
            */

        }catch (Exception e) {
            if (transaction != null && transaction.isActive())
                transaction.rollback();
            throw new DAOException("failed to set car status", e);
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }

     /**
     * Update number of instances in table books when reader take book
     * @param book_id book id
     * @throws DAOException exception
     */
    public void registerNewAbiturientResult(int abiturient_id, int subject_id, int mark) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            entityManager.getTransaction();

            entityManager.createNamedQuery("registerNewAbiturient", Abiturient.class)
            .setParameter(1, abiturient_id).setParameter(2, subject_id)
            .setParameter(3, mark);
            /* 
            Book book = entityManager.find(Book.class, book_id);

            transaction.begin();
            book.setNumber_of_instance(book.getNumber_of_instance() - 1);
            transaction.commit();
            */

        }catch (Exception e) {
            if (transaction != null && transaction.isActive())
                transaction.rollback();
            throw new DAOException("failed to set car status", e);
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }

}
