package utils;

import model.Race;

public interface RaceDAOInterface {
     /**
      * Returns race by id
      * @param id race id
      * @return race
      */
     Race readRace(int id);

     /**
      * Deletes race by id
      * @param id race id
      */
     void deleteRace(int id);

     /**
      * Updates race by id
      * @param race
      */
     void updateRace(Race race);

     /**
      * Inserts race
      * @param race race
      */
     void createRace(Race race);
}
