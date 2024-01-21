package model.dao;

import model.entity.Abiturient;
import model.entity.Abiturient_;
import model.entity.EList;
import model.entity.Faculty;
import model.entity.Subject;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Join;
import javax.persistence.criteria.JoinType;
import javax.persistence.criteria.Root;
import javax.transaction.Transactional;

//import org.seasar.doma.jdbc.criteria.Entityql;


import org.hibernate.Session;
import org.hibernate.SessionFactory;
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

            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Abiturient> cq = cb.createQuery(Abiturient.class);

            Root<Abiturient> abiturientRoot = cq.from(Abiturient.class);
            cq.where(cb.equal(abiturientRoot.get(Abiturient_.faculty_id), id));

            abiturientList = entityManager.createQuery(cq).getResultList();

        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return abiturientList;
    }

    public List<Subject> getListOfAllSubjects() {
        EntityManager entityManager = null;
        List<Subject> subjectList;
        try {

            entityManager = getEntityManagerFactory().createEntityManager();

            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Subject> cq = cb.createQuery(Subject.class);

            Root<Subject> subjectRoot = cq.from(Subject.class);

            subjectList = entityManager.createQuery(cq).getResultList();
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return subjectList;
    }

    /* 
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
    */

    /**
     * Update number of instances in table books when reader take book
     * @param book_id book id
     * @throws DAOException exception
     */

     @Transactional
     public void changeResultOfAbiturient(int abiturient_id, int new_mark) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
 
            // create update
            CriteriaUpdate<EList> update = cb.createCriteriaUpdate(EList.class);
    
            // set the root class
            Root<EList> e = update.from(EList.class);
    
            // set update and where clause
            update.set("mark", new_mark);
            update.where(cb.equal(e.get("abiturient_id"), abiturient_id));
    
            // perform update
            entityManager.createQuery(update).executeUpdate();

        }catch (Exception e) {
            if (transaction != null && transaction.isActive())
                transaction.rollback();
            throw new DAOException("failed to set car status", e);
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }
























    public void registerNewAbiturient(int abiturient_id, String surname, String first_name, String middle_name, int faculty_id) throws DAOException {
        EntityManager entityManager = null;
        EntityTransaction transaction = null;
        try {


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
