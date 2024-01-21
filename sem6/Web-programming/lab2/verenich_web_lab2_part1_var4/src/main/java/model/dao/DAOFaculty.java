package model.dao;

import model.entity.Abiturient;
import model.entity.Faculty;
import model.exception.DAOException;
import model.exception.JDBCConnectorException;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.Query;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DAOFaculty extends DAO {
    /**
     * Constructor
     * @throws DAOException exception
     */
    public DAOFaculty(){
        super();
    }

}
