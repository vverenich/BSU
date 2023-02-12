package by.verenich.callcenter;

public record Client(int id, CallCenter callCenter) implements Runnable {
    private static final long WAITING_TIME = 100;

    @Override
    public void run() {
        call();
    }

    private void call() {
        callCenter.takeClientCall(this, WAITING_TIME);
    }

    @Override
    public String toString() {
        return String.format("Client [id=%d]", this.id);
    }
}