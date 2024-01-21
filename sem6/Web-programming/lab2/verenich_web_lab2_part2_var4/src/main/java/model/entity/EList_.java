package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(EList.class)
public class EList_ {

    public static volatile SingularAttribute<Abiturient, Integer> list_id;
    public static volatile SingularAttribute<Abiturient, Integer> abiturient_id;
    public static volatile SingularAttribute<Abiturient, Integer> subject_id;
    public static volatile SingularAttribute<Abiturient, Integer> mark;
}