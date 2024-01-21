package connector;

import exceptions.DBAccessException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ResourceBundle;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * This class provide access to database
 */
public class DBConn {
    private static final String path = "database.properties";
    private static BlockingQueue<Connection> connectionQueue;
    private static int connectionCount;

    /**
     * Create connection pool
     *
     * @param connectionCount the size of pool
     * @throws DBAccessException if problem during connection occurred
     */
    static {
        try {
            startDB(10);
        } catch (DBAccessException ex) {
            ex.printStackTrace();
        }
    }

    public static void startDB(int connectionCount) throws DBAccessException {
        try {
            ResourceBundle resource = ResourceBundle.getBundle("database");
            String JDBC_DRIVER = resource.getString("driver");
            String DB_URL = resource.getString("url");
            String USER = resource.getString("user");
            String PASS = resource.getString("password");
            Class.forName(JDBC_DRIVER);
            DBConn.connectionCount = connectionCount;
            connectionQueue = new ArrayBlockingQueue<Connection>(connectionCount);
            for (int i = 0; i < connectionCount; ++i) {
                connectionQueue.add(DriverManager.getConnection(DB_URL, USER, PASS));
            }
        } catch (ClassNotFoundException e) {
            throw new DBAccessException("A problem with driver occurred " + e.getMessage());
        } catch (SQLException e) {
            throw new DBAccessException("Could not get connection " + e.getMessage());
        }
    }

    /**
     * Close connection pool
     *
     * @throws DBAccessException if problem during closing occurred
     */
    public static synchronized void stopDB() throws DBAccessException {
        try {
            for (int i = 0; i < connectionCount; ++i) {
                connectionQueue.take().close();
            }
        } catch (SQLException e) {
            throw new DBAccessException("Could not close database connection " + e.getMessage());
        } catch (InterruptedException e) {
            throw new DBAccessException("Problem with inner concurrent utils found " + e.getMessage());
        }
    }

    /**
     * Peek connection from pool. The connection must be returned!!!
     *
     * @return connection
     */
    public static synchronized Connection acquireConnection() {
        try {
            return connectionQueue.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        }
    }

    /**
     * Return the connection to pool
     *
     * @param conn to return
     */
    public static synchronized void releaseConnection(Connection conn) {
        connectionQueue.add(conn);
    }
}
