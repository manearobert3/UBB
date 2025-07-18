import mpi.*;
import java.util.Arrays;

public class NaiveFinalMPI {
    public static void main(String[] args) throws MPIException {
        //Initialize MPI
        MPI.Init(args);

        // basic MPI info
        int rank = MPI.COMM_WORLD.Rank();  // Rank of this process
        int size = MPI.COMM_WORLD.Size();  // Total number of processes

        int[] A = null;  // Polynomial A
        int[] B = null;  // Polynomial B
        int nA = 0;      // Size of polynomial A
        int nB = 0;      // Size of polynomial B

        // set polynomial data on the master (rank 0)
        if (rank == 0) {
            // Example polynomials A and B
            A = new int[]{3, 5, 7, 2, 8, 9, 6, 4};
            B = new int[]{6, 4, 3, 8, 1, 9, 2, 7};
            nA = A.length;
            nB = B.length;

            System.out.println("Master: A = " + Arrays.toString(A));
            System.out.println("Master: B = " + Arrays.toString(B));
        }

        // broadcast sizes of A and B to all processes
        int[] sizes = new int[2];
        if (rank == 0) {
            sizes[0] = nA;
            sizes[1] = nB;
        }
        MPI.COMM_WORLD.Bcast(sizes, 0, 2, MPI.INT, 0);
        nA = sizes[0];
        nB = sizes[1];

        // allocate memory for A and B in all processes
        if (rank != 0) {
            A = new int[nA];
            B = new int[nB];
        }

        // broadcast polynomials A and B to all processes
        MPI.COMM_WORLD.Bcast(A, 0, nA, MPI.INT, 0);
        MPI.COMM_WORLD.Bcast(B, 0, nB, MPI.INT, 0);

        //determine result size and local computations
        int resultSize = nA + nB - 1;
        int[] localResult = new int[resultSize];

        //divide the work among processes
        int chunk = (nA + size - 1) / size;  // Divide evenly, handle last process
        int start = rank * chunk;
        int end = Math.min(start + chunk, nA);  // Ensure no out-of-bounds

        // compute partial result for assigned range
        for (int i = start; i < end; i++) {
            for (int j = 0; j < nB; j++) {
                localResult[i + j] += A[i] * B[j];
            }
        }

        // gather partial results on master using MPI.Reduce
        int[] finalResult = new int[resultSize];
        MPI.COMM_WORLD.Reduce(localResult, 0, finalResult, 0, resultSize, MPI.INT, MPI.SUM, 0);

        if (rank == 0) {
            System.out.println("\nNaive MPI Result:");
            System.out.println(Arrays.toString(finalResult));
        }

        MPI.Finalize();
    }
}
