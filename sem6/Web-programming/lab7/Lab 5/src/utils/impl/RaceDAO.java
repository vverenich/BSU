package utils.impl;

import utils.RaceDAOInterface;
import model.Race;
import model.Race_;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Query;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * DAO class for Race entity
 */
@Stateless

public class RaceDAO extends DAO implements RaceDAOInterface {

    public RaceDAO(EntityManagerFactory emf) {
        super(emf);
    }

    public RaceDAO() {
        super();
    }

    public void createRace(Race entity) {
        createObject(entity);
    }

    public Race readRace(int id) {
        EntityManager entityManager = em;
        List<Race> results = null;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Race> query = cb.createQuery(Race.class);
        Root<Race> raceRoot = query.from(Race.class);
        query.where(cb.equal(raceRoot.get(Race_.id), id));
        results = entityManager.createQuery(query).getResultList();;

        if (results != null && results.size() != 0) {
            return results.get(0);
        }
        return null;
    }

    public void updateRace(Race entity) {
        EntityManager entityManager = em;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Race> updateRace = cb.createCriteriaUpdate(Race.class);
        Root<Race> employeeRoot = updateRace.from(Race.class);
        updateRace.set(Race_.brigadeId, entity.getBrigadeId());
        updateRace.set(Race_.capacity, entity.getCapacity());
        updateRace.set(Race_.planeId, entity.getPlaneId());
        updateRace.set(Race_.destination, entity.getDestination());
        updateRace.set(Race_.status, entity.getStatus());
        updateRace.set(Race_.distance, entity.getDistance());
        updateRace.where(cb.equal(employeeRoot.get(Race_.id), entity.getId()));
        entityManager.createQuery(updateRace).executeUpdate();
    }

    public void deleteRace(int id) {
        EntityManager entityManager = em;
        Query query = entityManager.createNamedQuery("Race.deleteById");
        query.setParameter("id", id);
        query.executeUpdate();
    }
}
