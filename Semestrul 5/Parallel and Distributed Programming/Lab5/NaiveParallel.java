public class NaiveParallel {

    public static int[] multiply(int A[], int B[], int numThreads) throws InterruptedException {
        int n = A.length;
        int m = B.length;
        int resultSize = n + m - 1;
        int[] C = new int[resultSize];

        Thread[] threads = new Thread[numThreads];

        for (int t = 0; t < numThreads; t++) {
            final int threadId = t;
            threads[t] = new Thread(() -> {
                for (int i = threadId; i < n; i += numThreads) {
                    for (int j = 0; j < m; j++) {
                        {
                            C[i + j] += A[i] * B[j];
                        }
                    }
                }
            });
            threads[t].start();
        }
        for (Thread thread : threads) {
            thread.join();
        }

        return C;
    }
}
