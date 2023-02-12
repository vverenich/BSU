package by.verenich.callcenter;

import java.util.Random;
import java.util.concurrent.atomic.AtomicReference;

import lombok.AccessLevel;
import lombok.AllArgsConstructor;
import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.RequiredArgsConstructor;
import lombok.Setter;
import lombok.ToString;
import lombok.extern.log4j.Log4j2;

@Getter
@Setter(AccessLevel.PRIVATE)
@EqualsAndHashCode
@AllArgsConstructor
@RequiredArgsConstructor
@ToString
@Log4j2
public class Operator {
    @ToString.Exclude
    private final Random timeRandomGenerator = new Random();

    private final int id;

    @ToString.Exclude
    private AtomicReference<Client> client = new AtomicReference<>();

    public synchronized void pickUpPhone(Client client) {
        this.client.set(client);
        System.out.println(this + " talking with: " + this.client.get());

        try {
            Thread.sleep(timeRandomGenerator.nextInt(100));
        } catch (InterruptedException e) {
            log.warn(e.getMessage());
        }

        this.client.set(null);
    }

    public boolean isBusy() {
        return client.get() != null;
    }
}
