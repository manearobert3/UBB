public class KaratsubaParallel {

    private static final int THRESHOLD = 1;

    public static int[] multiply(int[] A, int[] B, int numThreads) throws InterruptedException {
        int n = A.length;

        if (n <= THRESHOLD || numThreads <= 1) {
            return KaratsubaSequential.multiply(A, B);
        }

        int k = n / 2;

        int[] A0 = java.util.Arrays.copyOfRange(A, 0, k);
        int[] A1 = java.util.Arrays.copyOfRange(A, k, n);
        int[] B0 = java.util.Arrays.copyOfRange(B, 0, k);
        int[] B1 = java.util.Arrays.copyOfRange(B, k, n);

        int[][] results = new int[3][];
        Thread[] threads = new Thread[3];
        int threadsPerTask = numThreads / 3;

        // Ensure at least one thread per task
        if (threadsPerTask == 0) {
            threadsPerTask = 1;
        }

        // Task 1: Compute P0 = A0 * B0
        final int availableThreadsP0 = threadsPerTask;
        threads[0] = new Thread(() -> {
            try {
                results[0] = multiply(A0, B0, availableThreadsP0);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        threads[0].start();

        // Task 2: Compute P1 = A1 * B1
        final int availableThreadsP1 = threadsPerTask;
        threads[1] = new Thread(() -> {
            try {
                results[1] = multiply(A1, B1, availableThreadsP1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        threads[1].start();

        // Task 3: Compute P2 = (A0 + A1) * (B0 + B1)
        int[] A0A1 = addPolynomials(A0, A1);
        int[] B0B1 = addPolynomials(B0, B1);
        final int availableThreadsP2 = numThreads - 2 * threadsPerTask;
        threads[2] = new Thread(() -> {
            try {
                results[2] = multiply(A0A1, B0B1, availableThreadsP2 > 0 ? availableThreadsP2 : 1);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        threads[2].start();

        // Wait for all threads to complete
        for (Thread thread : threads) {
            thread.join();
        }

        int[] P0 = results[0];
        int[] P1 = results[1];
        int[] P2 = results[2];

        int[] middleTerm = subtractPolynomials(subtractPolynomials(P2, P0), P1);

        return combineTerms(P0, P1, middleTerm, k);
    }

    // Helper method: Add two polynomials
    private static int[] addPolynomials(int[] A, int[] B) {
        int maxLength = Math.max(A.length, B.length);
        int[] result = new int[maxLength];
        for (int i = 0; i < maxLength; i++) {
            int a = i < A.length ? A[i] : 0;
            int b = i < B.length ? B[i] : 0;
            result[i] = a + b;
        }
        return result;
    }

    // Helper method: Subtract two polynomials
    private static int[] subtractPolynomials(int[] A, int[] B) {
        int maxLength = Math.max(A.length, B.length);
        int[] result = new int[maxLength];
        for (int i = 0; i < maxLength; i++) {
            int a = i < A.length ? A[i] : 0;
            int b = i < B.length ? B[i] : 0;
            result[i] = a - b;
        }
        return result;
    }

    public static int[] combineTerms(int[] P0, int[] P1, int[] middleTerm, int k) {
        int maxLength = Math.max(P1.length + 2 * k, Math.max(P0.length, middleTerm.length + k));
        int[] result = new int[maxLength];

        // Add P0
        for (int i = 0; i < P0.length; i++) {
            result[i] += P0[i];
        }

        // Add middleTerm shifted by k
        for (int i = 0; i < middleTerm.length; i++) {
            result[i + k] += middleTerm[i];
        }

        // Add P1 shifted by 2k
        for (int i = 0; i < P1.length; i++) {
            result[i + 2 * k] += P1[i];
        }

        return (result);

    }
}
