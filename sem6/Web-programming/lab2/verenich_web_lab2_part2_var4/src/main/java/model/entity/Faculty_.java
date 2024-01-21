package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Faculty.class)
public class Faculty_ {

    public static volatile SingularAttribute<Abiturient, Integer> faculty_id;
    public static volatile SingularAttribute<Abiturient, String> title;

}