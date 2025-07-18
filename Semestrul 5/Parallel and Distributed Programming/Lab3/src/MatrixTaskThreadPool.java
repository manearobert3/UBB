public class MatrixTaskThreadPool implements Runnable {
    private final int i;
    private final int j;
    private final int[][] firstMatrix;
    private final int[][] secondMatrix;
    private final int[][] resultMatrix;

    public MatrixTaskThreadPool(int[][] firstMatrix, int[][] secondMatrix, int[][] resultMatrix, int i, int j) {
        this.firstMatrix = firstMatrix;
        this.secondMatrix = secondMatrix;
        this.resultMatrix = resultMatrix;
        this.i = i;
        this.j = j;
    }

    @Override
    public void run() {
        long threadId = Thread.currentThread().getId();
        System.out.println("Thread: " + threadId + " computing value for row: " + i + " and col: " + j);
        resultMatrix[i][j] = Main.calculateValue(firstMatrix, secondMatrix, i, j);
    }
}
