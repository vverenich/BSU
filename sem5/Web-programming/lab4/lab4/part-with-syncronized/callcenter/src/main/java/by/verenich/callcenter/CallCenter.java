package by.verenich.callcenter;

import java.util.List;

import lombok.extern.log4j.Log4j2;

@Log4j2
public record CallCenter(List<Operator> operators) {
    private static final int NUMBER_TRYING = 3;

    public void takeClientCall(Client client, long clientWaitingTime) {
        for (int i = 0; i < NUMBER_TRYING; ++i) {
            for (Operator operator : operators) {
                if (!operator.isBusy()) {
                    operator.pickUpPhone(client);
                    return;
                }
            }

            try {
                Thread.sleep(clientWaitingTime);
            } catch (InterruptedException e) {
                log.warn(e.getMessage());
            }
        }

        System.out.println("Client: " + client + " wait waited too much");
    }
}
