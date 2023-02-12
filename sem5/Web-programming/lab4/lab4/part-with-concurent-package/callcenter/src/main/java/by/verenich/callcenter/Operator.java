package by.verenich.callcenter;

import java.util.Random;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import lombok.AccessLevel;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.ToString;
import lombok.extern.log4j.Log4j2;

@Getter
@Setter(AccessLevel.PRIVATE)
@RequiredArgsConstructor
@ToString
@Log4j2
public class Operator {
    @ToString.Exclude
    private final Lock lock = new ReentrantLock();

    @ToString.Exclude
    private final Random timeRandomGenerator = new Random();

    private final int id;

    @ToString.Exclude
    private AtomicReference<Client> client = new AtomicReference<>();

    public void pickUpPhone(Client client) {
        lock.lock();
        try {
            this.client.set(client);
            System.out.println(this + " talking with: " + this.client.get());
    
            try {
                Thread.sleep(timeRandomGenerator.nextInt(100));
            } catch (InterruptedException e) {
                log.warn(e.getMessage());
            }
    
            this.client.set(null);
        } finally {
            lock.unlock();
        }
    }

    public boolean isBusy() {
        return client.get() != null;
    }
}
