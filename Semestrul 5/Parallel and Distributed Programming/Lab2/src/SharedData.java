import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SharedData {
    private int product;
    private boolean hasProduct = false; // Flag to indicate if a product is available
    private boolean done = false;       // Flag to indicate if production is complete
    private final Lock lock = new ReentrantLock();
    private final Condition condition = lock.newCondition();

    public void putProduct(int product) throws InterruptedException {
        lock.lock();
        try {
            while (hasProduct) {
                condition.await();
            }
            this.product = product;
            hasProduct = true;

            condition.signal();
        } finally {
            lock.unlock();
        }
    }

    public int getProduct() throws InterruptedException {
        lock.lock();
        try {
            while (!hasProduct && !done) {
                condition.await();
            }
            if (!hasProduct && done) {
                // No more products and production is complete
                return -1;
            }
            int product = this.product;
            hasProduct = false;
            // Signal the producer that the product has been consumed
            condition.signal();
            return product;
        } finally {
            lock.unlock();
        }
    }

    // Method to signal that production is complete
    public void setDone() {
        lock.lock();
        try {
            done = true;
            // Signal the consumer in case it's waiting
            condition.signalAll();
        } finally {
            lock.unlock();
        }
    }
}