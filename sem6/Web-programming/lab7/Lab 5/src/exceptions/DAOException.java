package exceptions;

/**
 * Exception class, to mark exceptions connected with data in database
 */
public class DAOException extends Exception{
    /**
     * Constructor with message
     * @param message to show
     */
    public DAOException(String message){
        super(message);
    }

    /**
     * Empty constructor
     */
    public DAOException(){
        super("Unknown DAO exception!");
    }
}