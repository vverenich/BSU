package exceptions;

/**
 * Wrong database access
 */
public class DBAccessException extends Exception{
    /**
     * Empty constructor
     */
    public DBAccessException(){
        super("Unknown database access exception!");
    }

    /**
     * Constructor with message
     * @param message to explain
     */
    public DBAccessException(String message){
        super(message);
    }
}
