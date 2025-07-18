public class Producer implements Runnable {
    private int[] vectorA;
    private int[] vectorB;
    private SharedData sharedData;

    public Producer(int[] vectorA, int[] vectorB, SharedData sharedData) {
        this.vectorA = vectorA;
        this.vectorB = vectorB;
        this.sharedData = sharedData;
    }

    @Override
    public void run() {
        try {
            int n = Math.min(vectorA.length, vectorB.length);
            for (int i = 0; i < n; i++) {
                int product = vectorA[i] * vectorB[i];
                sharedData.putProduct(product);
                System.out.println("Producer: Computed product " + product);
            }
            sharedData.setDone(); // Signal that production is complete
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}