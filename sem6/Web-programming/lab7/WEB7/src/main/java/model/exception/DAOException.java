package model.exception;

public class DAOException extends Throwable
{
    public DAOException(String message) {
        super(message);
    }

    public DAOException(String message, Throwable e) {
        super(message, e);
    }

    @Override
    public String getMessage() {
        return super.getMessage();
    }

    @Override
    public void printStackTrace() {
        super.printStackTrace();
    }
}