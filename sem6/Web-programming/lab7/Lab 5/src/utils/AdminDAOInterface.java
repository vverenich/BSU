package utils;
import model.Brigade;
import model.Race;

import javax.ejb.Remote;
import java.util.List;

public interface AdminDAOInterface {
     /**
      * Returns brigade by race id
      * @param id race id
      * @return brigade
      */
     Brigade getBrigadeByRaceId(Integer id);

     /**
      * Returns all races
      * @return list of races
      */
     List<Race> getAllRaces();

     /**
      * Cancels race
      * @param id race id to cancel
      */
     void cancelRaceById(Integer id);

     /**
      * Updates destination of race
      * @param id race id
      * @param newDestination new destination
      */
     void updateDestinationById(Integer id, String newDestination);

     /**
      * Returns all delayed races
      * @return
      */
     List<Race> getDelayedRaces();
}
