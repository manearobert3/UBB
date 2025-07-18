
import mpi.*;  // Use MPJ Express or any MPI wrapper in Java

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class RecursiveKaratsuba {

    // -------------------------------------------
    // MPI TAGS
    // -------------------------------------------
    private static final int TAG_SUBPROBLEM = 100;
    private static final int TAG_RESULT     = 200;
    private static final int TAG_STOP       = 999;

    // For controlling recursion
    private static final int THRESHOLD      = 3;
    private static final int MIN_SPLIT_SIZE = 3;   // Minimum polynomial length to try splitting

    public static void main(String[] args) throws Exception {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        // Just an example polynomial
        int[] A = {3, 5, 7, 2, 8, 9, 6, 4};
        int[] B = {6, 4, 3, 8, 1, 9, 2, 7};

        if (rank == 0) {
            // Rank 0 is the ultimate master
            // Build a list of all other ranks [1..size-1]
            List<Integer> freeRanks = new ArrayList<>();
            for (int r = 1; r < size; r++) {
                freeRanks.add(r);
            }

            // Master does the multi-level Karatsuba (using itself as sub-master for the top problem)
            int[] result = multiplyKaratsubaDistributed(A, B, freeRanks);

            // Print out the final result polynomial
            System.out.println("Final Result (rank 0): ");
            for (int i = 0; i < result.length; i++) {
                System.out.print(result[i] + " ");
            }
            System.out.println();

            // Convert to BigInteger (just for demonstration)
            BigInteger bigVal = arrayToBigInteger(handleAsNumbers(result));
            System.out.println("As BigInteger: " + bigVal);

            // Send STOP to all ranks
            for (int r = 1; r < size; r++) {
                MPI.COMM_WORLD.Send(new int[]{0}, 0, 1, MPI.INT, r, TAG_STOP);
            }
        } else {
            // Worker loop: each worker can become a "sub-master" if needed
            workerLoop();
        }

        MPI.Finalize();
    }


     //freeRanks a list of ranks we can use for parallel subproblems

    public static int[] multiplyKaratsubaDistributed(int[] A, int[] B, List<Integer> freeRanks) {
        // If small or not enough ranks, do sequential
        if (A.length <= THRESHOLD || B.length <= THRESHOLD || freeRanks.size() < 3 ||
                A.length < MIN_SPLIT_SIZE || B.length < MIN_SPLIT_SIZE) {
            return KaratsubaSequential.multiply(A, B);
        }

        // Otherwise, do standard Karatsuba splitting
        int n = Math.max(A.length, B.length);
        // Pad polynomials so they're the same length (for conceptual clarity)
        A = padPoly(A, n);
        B = padPoly(B, n);

        int k = n / 2;
        int[] A0 = Arrays.copyOfRange(A, 0, k);
        int[] A1 = Arrays.copyOfRange(A, k, n);
        int[] B0 = Arrays.copyOfRange(B, 0, k);
        int[] B1 = Arrays.copyOfRange(B, k, n);

        // A0A1 = A0 + A1, B0B1 = B0 + B1
        int[] A0A1 = addPolynomials(A0, A1);
        int[] B0B1 = addPolynomials(B0, B1);

        // We'll try to spawn 3 sub tasks: P0 = A0*B0, P1 = A1*B1, P2=(A0+A1)*(B0+B1)
        // ensure we have at least 3 free ranks. If not, do it sequentially.

        int freeNeeded = 3; // We want to use 3 distinct ranks
        if (freeRanks.size() < freeNeeded) {
            // not enough ranks to do full parallel => do sequential (or partial parallel)
            int[] p0Seq = multiplyKaratsubaDistributed(A0, B0, freeRanks);
            int[] p1Seq = multiplyKaratsubaDistributed(A1, B1, freeRanks);
            int[] p2Seq = multiplyKaratsubaDistributed(A0A1, B0B1, freeRanks);
            return combineTerms(p0Seq, p1Seq, subtractPolynomials(subtractPolynomials(p2Seq, p0Seq), p1Seq), k);
        }

        // Otherwise, we do the 3 tasks in parallel on 3 different ranks
        int rankP0 = freeRanks.remove(0);
        int rankP1 = freeRanks.remove(0);
        int rankP2 = freeRanks.remove(0);

        // Spawn tasks
        spawnSubproblem(A0, B0, rankP0);
        spawnSubproblem(A1, B1, rankP1);
        spawnSubproblem(A0A1, B0B1, rankP2);

        // Get results from each
        int[] p0 = receiveResult(rankP0);
        int[] p1 = receiveResult(rankP1);
        int[] p2 = receiveResult(rankP2);

        // Return those ranks to the pool
        freeRanks.add(rankP0);
        freeRanks.add(rankP1);
        freeRanks.add(rankP2);

        // middleTerm = p2 - p0 - p1
        int[] middleTerm = subtractPolynomials(subtractPolynomials(p2, p0), p1);

        return combineTerms(p0, p1, middleTerm, k);
    }

    //Send a subproblem to a rank
    private static void spawnSubproblem(int[] A, int[] B, int destRank) {
        // Step 1) send length info
        int[] meta = new int[]{A.length, B.length};
        MPI.COMM_WORLD.Send(meta, 0, 2, MPI.INT, destRank, TAG_SUBPROBLEM);
        // Step 2) send the actual arrays
        MPI.COMM_WORLD.Send(A, 0, A.length, MPI.INT, destRank, TAG_SUBPROBLEM);
        MPI.COMM_WORLD.Send(B, 0, B.length, MPI.INT, destRank, TAG_SUBPROBLEM);
    }

    //Receive result polynomial from a rank

    private static int[]    receiveResult(int srcRank) {
        int[] lengthBuf = new int[1];
        MPI.COMM_WORLD.Recv(lengthBuf, 0, 1, MPI.INT, srcRank, TAG_RESULT);
        int length = lengthBuf[0];

        int[] result = new int[length];
        MPI.COMM_WORLD.Recv(result, 0, length, MPI.INT, srcRank, TAG_RESULT);
        return result;
    }


    private static void workerLoop() {
        while (true) {
            // Probe to figure out what message is incoming
            Status status = MPI.COMM_WORLD.Probe(MPI.ANY_SOURCE, MPI.ANY_TAG);

            if (status.tag == TAG_STOP) {
                // Master says "we're done," break
                int[] dummy = new int[1];
                MPI.COMM_WORLD.Recv(dummy, 0, 1, MPI.INT, status.source, TAG_STOP);
                break;
            }

            if (status.tag == TAG_SUBPROBLEM) {
                // Receive meta
                int[] meta = new int[2];
                MPI.COMM_WORLD.Recv(meta, 0, 2, MPI.INT, status.source, TAG_SUBPROBLEM);
                int lenA = meta[0];
                int lenB = meta[1];

                // Receive the polynomials
                int[] A = new int[lenA];
                int[] B = new int[lenB];
                MPI.COMM_WORLD.Recv(A, 0, lenA, MPI.INT, status.source, TAG_SUBPROBLEM);
                MPI.COMM_WORLD.Recv(B, 0, lenB, MPI.INT, status.source, TAG_SUBPROBLEM);

                int[] partial = KaratsubaSequential.multiply(A, B);

                //Send the result back
                sendResult(partial, status.source);
            }
        }
    }

    private static void sendResult(int[] polynomial, int destRank) {
        // 1) send length
        MPI.COMM_WORLD.Send(new int[]{polynomial.length}, 0, 1, MPI.INT, destRank, TAG_RESULT);
        // 2) send the polynomial data
        MPI.COMM_WORLD.Send(polynomial, 0, polynomial.length, MPI.INT, destRank, TAG_RESULT);
    }

    public static class KaratsubaSequential {

        public static int[] multiply(int[] A, int[] B) {
            int n = A.length + B.length - 1;
            int[] C = new int[n];
            for (int i = 0; i < A.length; i++) {
                for (int j = 0; j < B.length; j++) {
                    C[i + j] += A[i] * B[j];
                }
            }
            return C;
        }
    }

     // Zero-pad polynomial array to length n if it's shorter.
    private static int[] padPoly(int[] poly, int n) {
        if (poly.length >= n) {
            return poly;
        }
        int[] result = new int[n];
        System.arraycopy(poly, 0, result, 0, poly.length);
        return result;
    }

    // Add polynomials
    private static int[] addPolynomials(int[] A, int[] B) {
        int maxLength = Math.max(A.length, B.length);
        int[] result = new int[maxLength];
        for (int i = 0; i < maxLength; i++) {
            int a = (i < A.length) ? A[i] : 0;
            int b = (i < B.length) ? B[i] : 0;
            result[i] = a + b;
        }
        return result;
    }

    // Subtract polynomials
    private static int[] subtractPolynomials(int[] A, int[] B) {
        int maxLength = Math.max(A.length, B.length);
        int[] result = new int[maxLength];
        for (int i = 0; i < maxLength; i++) {
            int a = (i < A.length) ? A[i] : 0;
            int b = (i < B.length) ? B[i] : 0;
            result[i] = a - b;
        }
        return result;
    }

    // Karatsuba combine
    private static int[] combineTerms(int[] P0, int[] P1, int[] middleTerm, int k) {
        int maxLength = Math.max(P1.length + 2*k,
                Math.max(P0.length, middleTerm.length + k));
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
            result[i + 2*k] += P1[i];
        }

        return result;
    }

    private static int[] handleAsNumbers(int[] c) {
        int carry = 0;
        List<Integer> resultList = new ArrayList<>();

        for (int i = 0; i < c.length; i++) {
            int value = c[i] + carry;
            resultList.add(value % 10);
            carry = value / 10;
        }
        while (carry > 0) {
            resultList.add(carry % 10);
            carry /= 10;
        }

        // Remove trailing zeros from the *end* of the array
        int endIndex = resultList.size() - 1;
        while (endIndex > 0 && resultList.get(endIndex) == 0) {
            endIndex--;
        }
        // Truncate
        resultList = resultList.subList(0, endIndex + 1);

        // Convert to int[]
        return resultList.stream().mapToInt(i -> i).toArray();
    }


    private static BigInteger arrayToBigInteger(int[] array) {
        StringBuilder sb = new StringBuilder();
        // The array is least-significant-digit first, so traverse from the end
        for (int i = array.length - 1; i >= 0; i--) {
            sb.append(array[i]);
        }
        return new BigInteger(sb.toString());
    }
}
