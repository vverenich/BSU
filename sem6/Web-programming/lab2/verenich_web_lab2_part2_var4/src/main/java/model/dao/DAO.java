package model.dao;

import model.connector.JDBCConnector;
import model.connector.JDBCConnectorPool;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

public class DAO {

    /**
     * JDBCConnectorPool object
     */
    protected JDBCConnectorPool connector;
    private static String PERSISTENCE_UNIT_NAME = "persistenceUnitName";
    private EntityManagerFactory factory;

    /**
     * Constructor
     * @throws DAOException exception
     */
    DAO() {
        factory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME);
    }

    protected EntityManagerFactory getEntityManagerFactory() {
        return factory;
    }
}
