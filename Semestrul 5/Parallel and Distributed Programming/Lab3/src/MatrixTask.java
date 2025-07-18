public class MatrixTask implements Runnable {
    private final int index;
    private final int[][] firstMatrix;
    private final int[][] secondMatrix;
    private final int[][] resultMatrix;
    private final String taskType;
    private final int numTasks;

    public MatrixTask(int[][] firstMatrix, int[][] secondMatrix, int[][] resultMatrix, int index, String taskType, int numTasks) {
        this.firstMatrix = firstMatrix;
        this.secondMatrix = secondMatrix;
        this.resultMatrix = resultMatrix;
        this.index = index;
        this.taskType = taskType;
        this.numTasks = numTasks;
    }

    @Override
    public void run() {
        long threadId = Thread.currentThread().threadId();
        Main.computePart(taskType, firstMatrix, secondMatrix, resultMatrix, index, numTasks, threadId);
    }
}
