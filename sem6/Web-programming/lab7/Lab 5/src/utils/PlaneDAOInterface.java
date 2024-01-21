package utils;
import model.Plane;

import javax.ejb.Remote;

public interface PlaneDAOInterface {
    /**
     * Returns employee by id
     * @param id employee id
     * @return employee
     */
     Plane readPlane(int id);

    /**
     * Deletes plane by id
     * @param id plane id
     */
     void deletePlane(int id);

    /**
     * Updates plane by id
     * @param plane
     */
     void updatePlane(Plane plane);

    /**
     * Inserts plane
     * @param plane plane
     */
     void createPlane(Plane plane);
}
