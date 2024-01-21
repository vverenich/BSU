package utils.impl;

import utils.BrigadeDAOInterface;
import model.Brigade;
import model.Brigade_;
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
 * DAO class for Brigade entity
 */
@Stateless

public class BrigadeDAO extends DAO implements BrigadeDAOInterface {

    public BrigadeDAO(EntityManagerFactory emf) {
        super(emf);
    }

    public BrigadeDAO() {
        super();
    }

    public void createBrigade(Brigade entity) {
        createObject(entity);
    }

    public Brigade readBrigade(int id) {
        EntityManager entityManager = em;
        List<Brigade> results = null;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Brigade> query = cb.createQuery(Brigade.class);
        Root<Brigade> brigadeRoot = query.from(Brigade.class);
        query.where(cb.equal(brigadeRoot.get(Brigade_.id), id));
        results = entityManager.createQuery(query).getResultList();;

        if (results != null && results.size() != 0) {
            return results.get(0);
        }

        return null;
    }

    public void updateBrigade(Brigade entity) {
        EntityManager entityManager = em;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Brigade> updateBrigade = cb.createCriteriaUpdate(Brigade.class);
        Root<Brigade> brigadeRoot = updateBrigade.from(Brigade.class);
        updateBrigade.set(Brigade_.commanderId, entity.getCommanderId());
        updateBrigade.where(cb.equal(brigadeRoot.get(Brigade_.id), entity.getId()));
        entityManager.createQuery(updateBrigade).executeUpdate();
    }

    public void deleteBrigade(int id){
        EntityManager entityManager = em;
        Query query = entityManager.createNamedQuery("Brigade.deleteById");
        query.setParameter("id", id);
        int count = query.executeUpdate();

    }
}
