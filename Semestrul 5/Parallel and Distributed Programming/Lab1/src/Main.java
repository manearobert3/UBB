import java.util.*;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        VariableSystem system = new VariableSystem();
        Scanner scanner = new Scanner(System.in);

        // Prompt user for inputs
        System.out.print("Enter number of primary variables: ");
        int numPrimary = scanner.nextInt();

        System.out.print("Enter number of secondary variables: ");
        int numSecondary = scanner.nextInt();

        System.out.print("Enter number of threads: ");
        int numThreads = scanner.nextInt();

        System.out.print("Enter number of operations per thread: ");
        int numUpdatesPerThread = scanner.nextInt();

        // Create primary variables (IDs 1 to numPrimary)
        for (int i = 1; i <= numPrimary; i++) {
            system.createVariable(i);
        }

        // Create secondary variables and set up dependencies
        // Each secondary variable depends on two random variables
        Random rand = new Random();

        for (int i = numPrimary + 1; i <= numPrimary + numSecondary; i++) {
            Variable var = system.createVariable(i);

            // Randomly select input variables from IDs 1 to i - 1
            int input1Id = rand.nextInt(i - 1) + 1;
            int input2Id = rand.nextInt(i - 1) + 1;

            Variable input1 = system.getVariable(input1Id);
            Variable input2 = system.getVariable(input2Id);

            var.addInput(input1);
            var.addInput(input2);
        }

        // Start timing
        long startTime = System.nanoTime();

        // Create threads to update primary variables
        List<Thread> threads = new ArrayList<>();

        for (int t = 0; t < numThreads; t++) {
            int threadNumber = t + 1; // For naming threads starting from 1
            Thread thread = new Thread(() -> {
                Random threadRand = new Random();
                for (int i = 0; i < numUpdatesPerThread; i++) {
                    int varId = threadRand.nextInt(numPrimary) + 1;
                    int newValue = threadRand.nextInt(100);

                    Variable var = system.getVariable(varId);
                    var.updatePrimaryValue(newValue);
                }
            });
            thread.setName("Thread-" + threadNumber);
            threads.add(thread);
            thread.start();
        }

        // Wait for all threads to finish
        for (Thread thread : threads) {
            thread.join();
        }

        // Stop timing
        long endTime = System.nanoTime();

        // Perform consistency check
        if (system.checkConsistency()) {
            System.out.println("Consistency check passed.");
        } else {
            System.out.println("Consistency check failed.");
        }

        // Calculate and print execution time
        double elapsedTimeInSec = (endTime - startTime) / 1_000_000_000.0;
        System.out.printf("Execution time: %.6f seconds%n", elapsedTimeInSec);
    }
}
