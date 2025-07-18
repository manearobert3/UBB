public class Consumer implements Runnable {
    private SharedData sharedData;
    private int sum = 0;

    public Consumer(SharedData sharedData) {
        this.sharedData = sharedData;
    }

    @Override
    public void run() {
        try {
            while (true) {
                int product = sharedData.getProduct();
                if (product == -1) {
                    // No more products to consume
                    break;
                }
                sum += product;
                System.out.println("Consumer: Consumed product " + product + ", Current Sum: " + sum);
            }
            System.out.println("Final Scalar Product (Dot Product) is: " + sum);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}