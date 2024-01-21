package model.DAO;

import model.Connector.JdbcConnectionPool;
import model.Connector.Exceptions.JDBCConnectionException;
import model.DAO.Exceptions.DAOException;

import com.mysql.cj.conf.ConnectionUrlParser;

import static model.Connector.JdbcConnectionPool.releaseConnection;

import java.sql.*;

abstract public class DAO {

    protected JdbcConnectionPool dbConnectorPool;   // Переменная для хранения пула соединений

    protected DAO() throws JDBCConnectionException {
        dbConnectorPool = JdbcConnectionPool.getInstance();
    }

    protected ConnectionUrlParser.Pair<PreparedStatement, ResultSet> executeStatement(String query, int operation_num, String operation_info) throws DAOException, JDBCConnectionException {
        Connection currConn;
        PreparedStatement currPs;
        try {
            currConn = JdbcConnectionPool.getConnection();
            currPs = currConn.prepareStatement(query);
            switch (operation_num) {
                case 0 -> {
                }
                case 1, 2, 3 -> {
                    try { // Добавляем в запрос нужный id факультета
                        currPs.setInt(1, Integer.parseInt(operation_info));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put faculty's ID to query.", throwables);
                    }
                }
            }
        } catch (SQLException | JDBCConnectionException throwables) {
            throw new DAOException("Error! Can't compile PreparedStatement!", throwables);
        }
        try {
            ResultSet rs = currPs.executeQuery();
            releaseConnection(currConn);
            return new ConnectionUrlParser.Pair<>(currPs, rs);
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't execute PreparedStatement!", throwables);
        }
    }

    protected void executeUpdateStatement(String query, int operation_num, String operation_info) throws DAOException, JDBCConnectionException {
        Connection currConn;
        PreparedStatement currPs;
        try {
            currConn = JdbcConnectionPool.getConnection();
            currPs = currConn.prepareStatement(query);
            switch (operation_num) {
                case 4 -> {
                    try { 
                        String[] operation_info_parts = operation_info.split("\\|");
                        currPs.setString(1, operation_info_parts[0]);
                        currPs.setString(2, operation_info_parts[1]);
                        currPs.setString(3, operation_info_parts[2]);
                        currPs.setInt(4, Integer.parseInt(operation_info_parts[3]));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put surname, first name, middle name or faculty's ID to query.", throwables);
                    }
                }

                case 5 -> {
                    try { 
                        String[] operation_info_parts = operation_info.split("\\|");
                        currPs.setInt(1, Integer.parseInt(operation_info_parts[0]));
                        currPs.setInt(2, Integer.parseInt(operation_info_parts[1]));
                        currPs.setInt(3, Integer.parseInt(operation_info_parts[2]));
                    } catch (SQLException throwables) {
                        throw new DAOException("Error! Can't put surname, abiturient_id, subject_id, mark to query.", throwables);
                    }
                }
            }
        } catch (SQLException | JDBCConnectionException throwables) {
            throw new DAOException("Error! Can't compile PreparedStatement!", throwables);
        }
        try {
            currPs.executeUpdate();
            releaseConnection(currConn);
            closePreparedStatement(currPs);
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't execute update-PreparedStatement!", throwables);
        }
    }

    protected void closeResultSet(ResultSet rs) throws DAOException {
        try {
            rs.close();
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't close ResultSet!", throwables);
        }
    }

    protected void closePreparedStatement(PreparedStatement ps) throws DAOException {
        try {
            ps.close();
        } catch (SQLException throwables) {
            throw new DAOException("Error! Can't close PreparedStatement!", throwables);
        }
    }

}
