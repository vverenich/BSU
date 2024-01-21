package utils.impl;

import utils.AdminDAOInterface;
import model.Brigade;
import model.Race;
import model.Race_;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * Class for administrator. Provides required functional.
 */
@Stateless

public class AdminDAO extends DAO implements AdminDAOInterface {

    public AdminDAO(EntityManagerFactory emf) {
        super(emf);
    }

    public AdminDAO() {
        super();
    }

    public Brigade getBrigadeByRaceId(Integer id) {
        Race race = null;
        race = (new RaceDAO()).readRace(id);
        Brigade brigade = race.getBrigade();
        return brigade;
    }

    public List<Race> getAllRaces() {
        EntityManager entityManager = em;
        List<Race> results = null;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Race> query = cb.createQuery(Race.class);
        Root<Race> raceRoot = query.from(Race.class);
        results = entityManager.createQuery(query).getResultList();
        if (results != null && results.size() != 0) {
            return results;
        }
        return null;
    }

    public void cancelRaceById(Integer id){
        EntityManager entityManager = em;

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Race> updateEmployee = cb.createCriteriaUpdate(Race.class);
        Root<Race> raceRoot = updateEmployee.from(Race.class);
        updateEmployee.set(Race_.status, "Cancelled");
        updateEmployee.where(cb.equal(raceRoot.get(Race_.id), id));
        entityManager.createQuery(updateEmployee).executeUpdate();
    }

    public void updateDestinationById(Integer id, String newDestination) {
        EntityManager entityManager = em;

        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Race> updateEmployee = cb.createCriteriaUpdate(Race.class);
        Root<Race> raceRoot = updateEmployee.from(Race.class);
        updateEmployee.set(Race_.destination, newDestination);
        updateEmployee.where(cb.equal(raceRoot.get(Race_.id), id));
        entityManager.createQuery(updateEmployee).executeUpdate();
    }

    public List<Race> getDelayedRaces() {

        EntityManager entityManager = em;
        List<Race> results = null;
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Race> query = cb.createQuery(Race.class);
            Root<Race> raceRoot = query.from(Race.class);
            query.where(cb.equal(raceRoot.get(Race_.status), "Cancelled"));
            results = entityManager.createQuery(query).getResultList();
        if (results != null && results.size() != 0) {
            return results;
        }
        return null;
    }
}
