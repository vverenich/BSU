package model;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Race.class)public class Race_ {
    public static volatile SingularAttribute<Race, Integer> id;
    public static volatile SingularAttribute<Race, Integer> capacity;
    public static volatile SingularAttribute<Race, Integer> brigadeId;
    public static volatile SingularAttribute<Race, String> destination;
    public static volatile SingularAttribute<Race, Integer> distance;
    public static volatile SingularAttribute<Race, Integer> planeId;
    public static volatile SingularAttribute<Race, String> status;
}