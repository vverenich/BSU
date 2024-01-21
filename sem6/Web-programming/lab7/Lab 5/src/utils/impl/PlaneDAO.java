package utils.impl;

import utils.PlaneDAOInterface;
import model.Plane;
import model.Plane_;
import javax.ejb.Stateless;
import javax.persistence.*;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * DAO class for Plane entity
 */
@Stateless

public class PlaneDAO extends DAO implements PlaneDAOInterface {

    public PlaneDAO(EntityManagerFactory emf) {
        super(emf);
    }

    public PlaneDAO() {
        super();
    }

    public void createPlane(Plane entity) {
        createObject(entity);
    }

    public Plane readPlane(int id) {
        EntityManager entityManager = em;
        List<Plane> results = null;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Plane> query = cb.createQuery(Plane.class);
        Root<Plane> planeRoot = query.from(Plane.class);
        query.where(cb.equal(planeRoot.get(Plane_.id), id));
        results = entityManager.createQuery(query).getResultList();

        if (results != null && results.size() != 0) {
            return results.get(0);
        }
        return null;
    }

    public void updatePlane(Plane entity){
        EntityManager entityManager = em;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Plane> updatePlane = cb.createCriteriaUpdate(Plane.class);
        Root<Plane> employeeRoot = updatePlane.from(Plane.class);
        updatePlane.set(Plane_.nmbr, entity.getNumber());
        updatePlane.set(Plane_.capacity, entity.getCapacity());
        updatePlane.where(cb.equal(employeeRoot.get(Plane_.id), entity.getId()));
        entityManager.createQuery(updatePlane).executeUpdate();

    }

    public void deletePlane(int id) {
        EntityManager entityManager = em;
        Query query = entityManager.createNamedQuery("Plane.deleteById");
        query.setParameter("id", id);
        int count = query.executeUpdate();
    }
}
