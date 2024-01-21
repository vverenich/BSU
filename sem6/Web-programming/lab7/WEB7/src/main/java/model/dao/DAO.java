package model.dao;

import model.JPAManager;

import javax.persistence.EntityManager;

/**
 * Abstract DAO: describing connection methods
 */


abstract class DAO
{
    private EntityManager conn;

    public DAO()
    {
        conn = JPAManager.getInstance();
    }

    public EntityManager getEntityManager()
    {
        return conn;
    }
}