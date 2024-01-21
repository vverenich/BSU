package model;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Brigade.class)
public class Brigade_ {
    private static final long serialVersionUID = 1L;
    public static volatile SingularAttribute<Brigade, Integer> id;
    public static volatile SingularAttribute<Brigade, Integer> commanderId;
}
