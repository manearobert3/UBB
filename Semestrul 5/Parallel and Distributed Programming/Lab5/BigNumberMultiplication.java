import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class BigNumberMultiplication {

    public static int[] bigIntegerToArray(BigInteger number) {
        String numString = number.toString();
        int n = numString.length();
        int[] result = new int[n];

        for (int i = 0; i < n; i++) {
            result[i] = Character.getNumericValue(numString.charAt(i));
        }
        return result;
    }
    public static int[] handleAsNumbers(int[] c) {
        int carry = 0;
        List<Integer> resultList = new ArrayList<>();

        for (int i = 0; i < c.length; i++) {
            int value = c[i] + carry;
            resultList.add(value % 10);
            carry = value / 10;
        }

        // process remaining carry
        while (carry > 0) {
            resultList.add(carry % 10);
            carry /= 10;
        }

        // convert back to an array
        int[] result = resultList.stream().mapToInt(Integer::intValue).toArray();

        // remove leading zeros
        int endIndex = result.length - 1;
        while (endIndex > 0 && result[endIndex] == 0) {
            endIndex--;
        }

        return Arrays.copyOf(result, endIndex + 1);
    }


    public static BigInteger arrayToBigInteger(int[] array) {
        StringBuilder numString = new StringBuilder();

        // reverse the array to get the correct order of digits
        for (int i = array.length - 1; i >= 0; i--) {
            numString.append(array[i]);
        }

        return new BigInteger(numString.toString());
    }
    public static BigInteger  multiply(BigInteger A, BigInteger B) throws InterruptedException {
        // Convert BigInteger to arrays of integers
        int[] aArray = bigIntegerToArray(A);
        int[] bArray = bigIntegerToArray(B);

        // Use Karatsuba
        int[] resultArray = KaratsubaSequential.multiply(aArray, bArray);
        resultArray = handleAsNumbers(resultArray);

        return arrayToBigInteger(resultArray);
    }

}
