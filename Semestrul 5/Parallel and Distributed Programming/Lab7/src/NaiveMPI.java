import mpi.*;
import java.util.Arrays;

public class NaiveMPI {
    public static void main(String[] args) throws MPIException {
        // 1. Initialize MPI
        MPI.Init(args);

        // 2. Basic MPI info
        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        // -------------------------------
        // MASTER READS/PREPARES DATA
        // -------------------------------
        int[] A = null;  // polynomial A
        int[] B = null;  // polynomial B
        int nA = 0;
        int nB = 0;

        // Set polynomial data on the master
        if (rank == 0) {
            A = new int[]{3, 5, 7, 2, 8, 9, 6, 4};
            B = new int[]{6, 4, 3, 8, 1, 9, 2, 7};
            nA = A.length;
            nB = B.length;

            System.out.println("Master: A = " + Arrays.toString(A));
            System.out.println("Master: B = " + Arrays.toString(B));
        }

        // 3. Broadcast sizes
        int[] sizes = new int[2];
        if (rank == 0) {
            sizes[0] = nA;
            sizes[1] = nB;
        }
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        nA = sizes[0];
        nB = sizes[1];

        // 4. Allocate local A & B for all processes
        if (rank != 0) {
            A = new int[nA];
            B = new int[nB];
        }

        // 5. Broadcast polynomials A and B
        MPI.COMM_WORLD.Bcast(A, 0, nA, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(B, 0, nB, MPI.INT, 0);

        // The result size will be nA + nB - 1
        int resultSize = nA + nB - 1;
        int[] localResult = new int[resultSize];

        // 6. Divide the work among processes
        int chunk = nA / size;
        int start = rank * chunk;
        int end = (rank == size - 1) ? nA : start + chunk;

        // 7. Each process computes partial result
        for (int i = start; i < end; i++) {
            for (int j = 0; j < nB; j++) {
                localResult[i + j] += A[i] * B[j];
            }
        }

        // 8. Gather partial results on master
        int[] finalResult = new int[resultSize];
        MPI.COMM_WORLD.Reduce(localResult, 0, finalResult, 0,
                resultSize, MPI.INT, MPI.SUM, 0);

        // 9. Master prints the final result
        if (rank == 0) {
            System.out.println("\nNaive MPI Result:");
            System.out.println(Arrays.toString(finalResult));
        }

        // 10. Finalize MPI
        MPI.Finalize();
    }
}
