package model;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Plane.class)
public class Plane_ {
    public static volatile SingularAttribute<Plane, Integer> id;
    public static volatile SingularAttribute<Plane, String> nmbr;
    public static volatile SingularAttribute<Plane, Integer> capacity;
}
