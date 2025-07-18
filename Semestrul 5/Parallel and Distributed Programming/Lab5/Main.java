import java.math.BigInteger;

public class Main {
    public static void printArray(int[] A) {
        for (int i = 0; i < A.length; i++) {
            System.out.print(A[i] + "x" + i);
            if (i != A.length - 1) {
                System.out.print(" + ");
            } else {
                System.out.println("\n");
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {

        int[] A;
        int[] B;
        A = new int[]{3, 5, 7, 2, 8, 9, 6, 4};
        B = new int[]{6, 4, 3, 8, 1, 9, 2, 7};


        // Measure Naive Sequential
        long startTime = System.nanoTime();
        int[] C = NaiveSequential.multiply(A, B);
        long endTime = System.nanoTime();
        System.out.println("Naive Sequential Time: " + (endTime - startTime) / 1_000_000.0 + " ms");
        Main.printArray(C);

        // Measure Naive Parallel
        startTime = System.nanoTime();
        int[] D = NaiveParallel.multiply(A, B, 8);
        endTime = System.nanoTime();
        System.out.println("Naive Parallel Time: " + (endTime - startTime) / 1_000_000.0 + " ms");
        Main.printArray(D);

        // Measure Karatsuba Sequential
        startTime = System.nanoTime();
        int[] E = KaratsubaSequential.multiply(A, B);
        endTime = System.nanoTime();
        System.out.println("Karatsuba Sequential Time: " + (endTime - startTime) / 1_000_000.0 + " ms");
        Main.printArray(E);

        // Measure Karatsuba Parallel
        startTime = System.nanoTime();
        int[] F = KaratsubaParallel.multiply(A, B, 8);
        endTime = System.nanoTime();
        System.out.println("Karatsuba Parallel Time: " + (endTime - startTime) / 1_000_000.0 + " ms");
        Main.printArray(F);

        // Measure BigNumberMultiplication
        BigInteger X = new BigInteger("12345678901234567890");
        BigInteger Y = new BigInteger("98765432109876543210");
        startTime = System.nanoTime();
        BigInteger result = BigNumberMultiplication.multiply(X, Y);
        endTime = System.nanoTime();
        System.out.println("BigNumberMultiplication Time: " + (endTime - startTime) / 1_000_000.0 + " ms");

        System.out.println("Result of Multiplication:");
        System.out.println(result);
    }
}
