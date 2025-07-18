import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class Main extends Thread {

    static int SIZE = 9;

    static int[][] createMatrix() {
        int[][] newMatrix = new int[SIZE][SIZE];
        Random rand = new Random();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newMatrix[i][j] = rand.nextInt(100);
            }
        }
        return newMatrix;
    }

    static int[][] createEmptyMatrix() {
        return new int[SIZE][SIZE];
    }

    static int calculateValue(int[][] firstMatrix, int[][] secondMatrix, int i, int j) {
        int sum = 0;
        for (int m = 0; m < SIZE; m++) {
            sum += firstMatrix[i][m] * secondMatrix[m][j];
        }
        return sum;
    }

    static void computePart(String taskType, int[][] firstMatrix, int[][] secondMatrix, int[][] resultMatrix, int index, int numTasks, long threadId) {
        switch (taskType) {
            case "row" -> computeValuesRows(firstMatrix, secondMatrix, resultMatrix, index, numTasks, threadId);
            case "col" -> computeValuesCols(firstMatrix, secondMatrix, resultMatrix, index, numTasks, threadId);
            case "k-th" -> computeConsTasks(firstMatrix, secondMatrix, resultMatrix, index, numTasks, threadId);
        }
    }

    static void computeValuesRows(int[][] firstMatrix, int[][] secondMatrix, int[][] resultMatrix, int index, int numTasks, long threadId) {
        int totalElements = SIZE * SIZE;
        int elementsPerTask = totalElements / numTasks;
        int start = index * elementsPerTask;
        int end = (index == numTasks - 1) ? totalElements : start + elementsPerTask;

        for (int i = start; i < end; i++) {
            int row = i / SIZE;
            int col = i % SIZE;
            System.out.println("Thread: " + threadId + " computing values for row: " + row + " and col: " + col);
            resultMatrix[row][col] = calculateValue(firstMatrix, secondMatrix, row, col);
        }
    }

    static void computeValuesCols(int[][] firstMatrix, int[][] secondMatrix, int[][] resultMatrix, int index, int numTasks, long threadId) {
        int totalElements = SIZE * SIZE;
        int elementsPerTask = totalElements / numTasks;
        int start = index * elementsPerTask;
        int end = (index == numTasks - 1) ? totalElements : start + elementsPerTask;

        for (int i = start; i < end; i++) {
            int col = i / SIZE;
            int row = i % SIZE;
            System.out.println("Thread: " + threadId + " computing values for row: " + row + " and col: " + col);
            resultMatrix[row][col] = calculateValue(firstMatrix, secondMatrix, row, col);
        }
    }

    static void computeConsTasks(int[][] firstMatrix, int[][] secondMatrix, int[][] resultMatrix, int index, int numTasks, long threadId) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int elementIndex = i * SIZE + j;
                if (elementIndex % numTasks == index) {
                    System.out.println("Thread: " + threadId + " computing values for row: " + i + " and col: " + j);
                    resultMatrix[i][j] = calculateValue(firstMatrix, secondMatrix, i, j);
                }
            }
        }
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Options:\n1. Row-wise\n2. Column-wise\n3. Every k-th element\n4. Exit.");
            int choice = scanner.nextInt();
            if (choice == 4) break;

            String taskType = switch (choice) {
                case 1 -> "row";
                case 2 -> "col";
                case 3 -> "k-th";
                default -> throw new IllegalArgumentException("Invalid choice.");
            };

//            int[][] firstMatrix = createMatrix();
//            int[][] secondMatrix = createMatrix();
                        int[][] firstMatrix = {
                    {1, 2, 3, 4, 5, 6, 7, 8, 9},
                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
                    {1, 3, 5, 7, 9, 2, 4, 6, 8},
                    {8, 6, 4, 2, 9, 7, 5, 3, 1},
                    {2, 4, 6, 8, 1, 3, 5, 7, 9},
                    {9, 7, 5, 3, 1, 8, 6, 4, 2},
                    {3, 6, 9, 1, 4, 7, 2, 5, 8},
                    {8, 5, 2, 7, 4, 1, 6, 3, 9},
                    {7, 1, 3, 9, 5, 8, 2, 4, 6}
            };

            int[][] secondMatrix = {
                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
                    {1, 2, 3, 4, 5, 6, 7, 8, 9},
                    {8, 7, 6, 5, 4, 3, 2, 1, 9},
                    {9, 1, 2, 3, 4, 5, 6, 7, 8},
                    {2, 3, 4, 5, 6, 7, 8, 9, 1},
                    {1, 9, 8, 7, 6, 5, 4, 3, 2},
                    {3, 4, 5, 6, 7, 8, 9, 1, 2},
                    {6, 5, 4, 3, 2, 1, 9, 8, 7},
                    {7, 6, 5, 4, 3, 2, 1, 9, 8}
            };
            int[][] resultMatrix = createEmptyMatrix();

            System.out.print("Enter the number of tasks (threads): ");
            int numTasks = scanner.nextInt();

            System.out.print("Use thread pool? (yes/no): ");
            String useThreadPool = scanner.next();
            long startTime = System.nanoTime();

            if (useThreadPool.equalsIgnoreCase("yes")) {
                // Create a fixed thread pool
                ExecutorService executor = Executors.newFixedThreadPool(numTasks);

                // Submit tasks to the executor
                if (taskType.equals("k-th")) {
                    for (int i = 0; i < SIZE; i++) {
                        for (int j = 0; j < SIZE; j++) {
                                MatrixTaskThreadPool task = new MatrixTaskThreadPool(firstMatrix, secondMatrix, resultMatrix, i, j);
                                executor.submit(task);
                        }
                    }
                }

                // Shutdown the executor and wait for tasks to complete
                executor.shutdown();
                while (!executor.isTerminated()) {
                    // Wait for all tasks to finish
                }
            } else {
                // Create and start threads directly
                Thread[] threads = new Thread[numTasks];
                for (int i = 0; i < numTasks; i++) {
                    MatrixTask task = new MatrixTask(firstMatrix, secondMatrix, resultMatrix, i, taskType, numTasks);
                    threads[i] = new Thread(task);
                    threads[i].start();
                }

                for (Thread thread : threads) {
                    try {
                        thread.join();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
            }

            System.out.println("Resulting Matrix:");
            int[][] resultMatrixVerify = {
                {219, 228, 219, 210, 201, 192, 255, 264, 237},
                {241, 222, 221, 220, 219, 218, 235, 216, 233},
                {239, 195, 196, 197, 198, 199, 254, 291, 256},
                {193, 237, 236, 235, 234, 233, 259, 222, 176},
                {267, 213, 204, 195, 186, 177, 231, 258, 294},
                {221, 255, 244, 233, 222, 211, 236, 189, 214},
                {221, 256, 237, 218, 199, 180, 206, 241, 267},
                {264, 209, 208, 207, 206, 205, 231, 257, 238},
                {259, 239, 228, 217, 206, 195, 220, 245, 216}
        };
            boolean matricesAreEqual = Arrays.deepEquals(resultMatrixVerify, resultMatrix);
            System.out.println("Matrices are equal: " + matricesAreEqual);
            long endTime = System.nanoTime();
            System.out.println("Execution time is: " + (endTime - startTime) / 1000000);
        }
        scanner.close();
    }
}




//            int[][] firstMatrix = {
//                    {1, 2, 3, 4, 5, 6, 7, 8, 9},
//                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
//                    {1, 3, 5, 7, 9, 2, 4, 6, 8},
//                    {8, 6, 4, 2, 9, 7, 5, 3, 1},
//                    {2, 4, 6, 8, 1, 3, 5, 7, 9},
//                    {9, 7, 5, 3, 1, 8, 6, 4, 2},
//                    {3, 6, 9, 1, 4, 7, 2, 5, 8},
//                    {8, 5, 2, 7, 4, 1, 6, 3, 9},
//                    {7, 1, 3, 9, 5, 8, 2, 4, 6}
//            };
//
//            int[][] secondMatrix = {
//                    {9, 8, 7, 6, 5, 4, 3, 2, 1},
//                    {1, 2, 3, 4, 5, 6, 7, 8, 9},
//                    {8, 7, 6, 5, 4, 3, 2, 1, 9},
//                    {9, 1, 2, 3, 4, 5, 6, 7, 8},
//                    {2, 3, 4, 5, 6, 7, 8, 9, 1},
//                    {1, 9, 8, 7, 6, 5, 4, 3, 2},
//                    {3, 4, 5, 6, 7, 8, 9, 1, 2},
//                    {6, 5, 4, 3, 2, 1, 9, 8, 7},
//                    {7, 6, 5, 4, 3, 2, 1, 9, 8}
//            };
//        int[][] resultMatrix = {
//                {219, 228, 219, 210, 201, 192, 255, 264, 237},
//                {241, 222, 221, 220, 219, 218, 235, 216, 233},
//                {239, 195, 196, 197, 198, 199, 254, 291, 256},
//                {193, 237, 236, 235, 234, 233, 259, 222, 176},
//                {267, 213, 204, 195, 186, 177, 231, 258, 294},
//                {221, 255, 244, 233, 222, 211, 236, 189, 214},
//                {221, 256, 237, 218, 199, 180, 206, 241, 267},
//                {264, 209, 208, 207, 206, 205, 231, 257, 238},
//                {259, 239, 228, 217, 206, 195, 220, 245, 216}
//        };

