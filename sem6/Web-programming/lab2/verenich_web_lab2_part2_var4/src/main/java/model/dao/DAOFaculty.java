package model.dao;

import model.entity.Abiturient;
import model.entity.Faculty;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DAOFaculty extends DAO {
    /**
     * Constructor
     * @throws DAOException exception
     */
    public DAOFaculty(){
        super();
    }

    public double getAverageMarkOfTheFaculty(int id) {
        EntityManager entityManager = null;
        double mark = 7.4;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            /*
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Double> cq = cb.createQuery(Double.class);
            Root<List> root = cq.from(List.class);
            Join<Object, Object> abiturient = root.join(List_.)
            cq.select(cb.avg(cq))
            cq.where(cb.equal(abiturientRoot.get(Abiturient_.faculty_id), id));
               
            mark = entityManager.createQuery(cq).get
         */

 //           select avg(mark)
//                     from e_list
//                     left join e_abiturient on e_abiturient.abiturient_id = e_list.abiturient_id
//                     where e_abiturient.faculty_id = :id""", resultClass = Faculty.class),

        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
        return mark;
    }

    

}
