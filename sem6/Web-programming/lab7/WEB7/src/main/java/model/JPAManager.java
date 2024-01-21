package model;

import javax.persistence.EntityManager;
import javax.persistence.Persistence;

public class JPAManager
{
    private static JPAManager instance;
    private static EntityManager manager;

    private JPAManager ()
    {
        manager = Persistence.createEntityManagerFactory("COLIBRI").createEntityManager();
    }

    public static EntityManager getInstance()
    {
        if (instance == null)
        {
            instance = new JPAManager();
        }
        return manager;
    }

    public static void close()
    {
        manager.close();
    }
}