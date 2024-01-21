package utils;
import model.Brigade;

public interface BrigadeDAOInterface {
     /**
      * Returns brigade by id
      * @param id brigade id
      * @return brigade
      */
     Brigade readBrigade(int id);

    /**
     * Deletes brigade by id
      * @param id brigade id
      */
     void deleteBrigade(int id);

    /**
     * Updates brigade
      * @param brigade brigade id
      */
     void updateBrigade(Brigade brigade);

    /**
     * Inserts new brigade to db
      * @param brigade brigade
      */
     void createBrigade(Brigade brigade);
}
