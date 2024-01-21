package utils;

import model.Employee;

public interface EmployeeDAOInterface {

    /**
     * Returns employee by id
     * @param id employee id
     * @return employee
     */
    Employee readEmployee(int id);

    /**
     * Deletes employee by id
     * @param id employee id
     */
    void deleteEmployee(int id);

    /**
     * Updates employee by id
     * @param employee
     */
    void updateEmployee(Employee employee);

    /**
     * Inserts employee
     * @param employee employee
     */
    void createEmployee(Employee employee);
}
