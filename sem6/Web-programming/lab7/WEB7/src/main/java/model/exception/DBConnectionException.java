package model.exception;

public class DBConnectionException extends Throwable
{
    public DBConnectionException(String message) {
        super(message);
    }

    public DBConnectionException(String message, Throwable e) {
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
