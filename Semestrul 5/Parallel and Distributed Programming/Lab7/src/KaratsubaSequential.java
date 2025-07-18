public class KaratsubaSequential {

    public static int[] addPolynomials(int[] A, int[] B) {
        int maxLength = Math.max(A.length, B.length);
        int[] result = new int[maxLength];

        for (int i = 0; i < maxLength; i++) {
            int aCoeff = i < A.length ? A[i] : 0;
            int bCoeff = i < B.length ? B[i] : 0;
            result[i] = aCoeff + bCoeff;
        }
        return result;
    }
    public static int[] combineTerms(int[] P0, int[] P1, int[] middleTerm, int k) {
        int n = (P1.length + k * 2);
        int[] result = new int[n];

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
        return result;
    }


    public static int[] subtractPolynomials(int[] A, int[] B) {
        int maxLength = Math.max(A.length, B.length);
        int[] result = new int[maxLength];

        for (int i = 0; i < maxLength; i++) {
            int aCoeff = i < A.length ? A[i] : 0;
            int bCoeff = i < B.length ? B[i] : 0;
            result[i] = aCoeff - bCoeff;
        }
        return result;
    }


    public static int[] multiply(int[] A, int[] B) {
        int n = A.length;

        if (n == 1) {
            return new int[]{A[0] * B[0]};
        }

        int k = n / 2;

        int[] A0 = java.util.Arrays.copyOfRange(A, 0, k);
        int[] A1 = java.util.Arrays.copyOfRange(A, k, n);
        int[] B0 = java.util.Arrays.copyOfRange(B, 0, k);
        int[] B1 = java.util.Arrays.copyOfRange(B, k, n);

        int[] P0 = multiply(A0, B0);
        int[] P1 = multiply(A1, B1);
        int[] A0A1 = addPolynomials(A0, A1);
        int[] B0B1 = addPolynomials(B0, B1);
        int[] P2 = multiply(A0A1, B0B1);
        int[] middleTerm = subtractPolynomials(subtractPolynomials(P2, P0), P1);

        return combineTerms(P0, P1, middleTerm, k);
    }


}
