package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Subject.class)
public class Subject_ {

    public static volatile SingularAttribute<Abiturient, Integer> subject_id;
    public static volatile SingularAttribute<Abiturient, String> title;

}