public class NaiveSequential {

    public static int[] multiply(int[] A, int[] B) {
        int n = A.length;
        int m = B.length;
        int[] C = new int[n + m - 1];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                C[i + j] += A[i] * B[j];
            }
        }
        return C;

    }

}
