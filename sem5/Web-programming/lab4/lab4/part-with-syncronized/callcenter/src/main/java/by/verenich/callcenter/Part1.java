package by.verenich.callcenter;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.IntStream;

public class Part1 {
    private static final int OPERATORS_COUNT = 5;
    private static final int CLIENT_COUNT = 20;

    public static void main(String[] args) {

        List<Operator> operators = IntStream
            .rangeClosed(1, OPERATORS_COUNT)
            .mapToObj(Operator::new)
            .toList();

        CallCenter callCenter = new CallCenter(operators);
            
        List<Client> clients = IntStream
            .rangeClosed(1, CLIENT_COUNT)
            .mapToObj(id -> new Client(id, callCenter))
            .toList();

        ExecutorService executorService = Executors.newFixedThreadPool(CLIENT_COUNT);
        clients.forEach(executorService::execute);
        executorService.shutdown();
    }
}
