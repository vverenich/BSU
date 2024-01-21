package utils.impl;

import utils.EmployeeDAOInterface;
import model.Employee;
import model.Employee_;
import javax.ejb.Stateless;
import javax.persistence.*;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import java.util.List;

/**
 * DAO class for Employee entity
 */
@Stateless
public class EmployeeDAO extends DAO implements EmployeeDAOInterface {

    public EmployeeDAO(EntityManagerFactory emf) {
        super(emf);
    }

    public EmployeeDAO() {
        super();
    }

    public void createEmployee(Employee entity) {
        createObject(entity);
    }

    public Employee readEmployee(int id) {
        EntityManager entityManager = null;
        List<Employee> results = null;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaQuery<Employee> query = cb.createQuery(Employee.class);
        Root<Employee> employeeRoot = query.from(Employee.class);
        query.where(cb.equal(employeeRoot.get(Employee_.id), id));
        results = entityManager.createQuery(query).getResultList();

        if (results != null && results.size() != 0) {
            return results.get(0);
        }
        return null;
    }

    public void updateEmployee(Employee entity) {
        EntityManager entityManager = null;
        entityManager = em;
        CriteriaBuilder cb = entityManager.getCriteriaBuilder();
        CriteriaUpdate<Employee> updateEmployee = cb.createCriteriaUpdate(Employee.class);
        Root<Employee> employeeRoot = updateEmployee.from(Employee.class);
        updateEmployee.set(Employee_.name, entity.getName());
        updateEmployee.set(Employee_.position, entity.getPosition());
        updateEmployee.where(cb.equal(employeeRoot.get(Employee_.id), entity.getId()));
        entityManager.createQuery(updateEmployee).executeUpdate();
    }

    public void deleteEmployee(int id) {
        EntityManager entityManager = em;
        Query query = entityManager.createNamedQuery("Employee.deleteById");
        query.setParameter("id", id);
        int count = query.executeUpdate();
    }

}
