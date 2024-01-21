package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Abiturient.class)
public class Abiturient_ {

    public static volatile SingularAttribute<Abiturient, Integer> abiturient_id;
    public static volatile SingularAttribute<Abiturient, String> first_name;
    public static volatile SingularAttribute<Abiturient, String> surname;
    public static volatile SingularAttribute<Abiturient, String> middle_name;
    public static volatile SingularAttribute<Abiturient, Integer> faculty_id;

}