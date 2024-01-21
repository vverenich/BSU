package model.entity;

import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@StaticMetamodel(Client.class)
public class Client_
{
    public static volatile SingularAttribute<Client, Integer> id;
    public static volatile SingularAttribute<Client, String> name;
}
