//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {



    public static void main(String[] args) {

        int[] vectorA = {1, 2, 3, 4, 5};
        int[] vectorB = {6, 7, 8, 9, 10};

        SharedData sharedData = new SharedData();

        Producer producer = new Producer(vectorA, vectorB, sharedData);
        Consumer consumer = new Consumer(sharedData);

        Thread producerThread = new Thread(producer, "Producer");
        Thread consumerThread = new Thread(consumer, "Consumer");

        consumerThread.start(); // Start consumer first to ensure it waits for data
        producerThread.start();

        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}