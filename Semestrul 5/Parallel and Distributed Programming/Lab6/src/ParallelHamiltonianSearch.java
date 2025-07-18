
import java.util.*;
        import java.util.concurrent.*;
        import java.util.concurrent.atomic.AtomicBoolean;

public class ParallelHamiltonianSearch {
    private final AtomicBoolean solutionFound = new AtomicBoolean(false);

    private volatile List<Integer> solutionPath = null; // shared by all threads

    private final List<List<Integer>> adjacencyList;
    private final int n; // number of vertices

    private final ExecutorService executor;

    public ParallelHamiltonianSearch(List<List<Integer>> adjacencyList, int threadCount) {
        this.adjacencyList = adjacencyList;
        this.n = adjacencyList.size();
        this.executor = Executors.newFixedThreadPool(threadCount);
    }

    public List<Integer> findHamiltonianCycle(int start) {
        boolean[] visited = new boolean[n];
        visited[start] = true;
        List<Integer> path = new ArrayList<>();
        path.add(start);

        Future<?> future = executor.submit(() -> search(start, visited, path, start));

        try {
            future.get();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        } finally {
            executor.shutdownNow();
        }

        return solutionFound.get() ? solutionPath : null;
    }

    private void search(int current, boolean[] visited, List<Integer> path, int start) {
        if (solutionFound.get()) {
            return; // If a solution is found by any thread, stop
        }

        if (path.size() == n) {
            if (adjacencyList.get(current).contains(start)) {
                List<Integer> completePath = new ArrayList<>(path);
                completePath.add(start);
                solutionPath = completePath;
                solutionFound.set(true);
            }
            return;
        }

        List<Integer> neighbors = adjacencyList.get(current);

        for (int next : neighbors) {
            if (!visited[next] && !solutionFound.get()) {
                boolean[] newVisited = Arrays.copyOf(visited, n);
                newVisited[next] = true;
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(next);

                // Always create a new thread for every neighbor
                executor.submit(() -> search(next, newVisited, newPath, start));
            }
        }
    }

    public static void main(String[] args) {
        int threadCount = 4; // Adjust the number of threads in the pool

        List<List<Integer>> adjacencyListWithCycle = new ArrayList<>();
        adjacencyListWithCycle.add(Arrays.asList(1, 2)); // 0
        adjacencyListWithCycle.add(Arrays.asList(2, 3)); // 1
        adjacencyListWithCycle.add(Arrays.asList(3, 4)); // 2
        adjacencyListWithCycle.add(Arrays.asList(0, 4)); // 3
        adjacencyListWithCycle.add(Arrays.asList(1, 0)); // 4

        long startTime = System.nanoTime();

        ParallelHamiltonianSearch solverWithCycle =
                new ParallelHamiltonianSearch(adjacencyListWithCycle, threadCount);
        List<Integer> cycle = solverWithCycle.findHamiltonianCycle(0);

        long endTime = System.nanoTime();

        if (cycle != null) {
            System.out.println("Found Hamiltonian Cycle: " + cycle);
        } else {
            System.out.println("No Hamiltonian Cycle found");
        }
        System.out.println("Time for Test 1 (with cycle): " + (endTime - startTime) / 1_000_000 + " ms");

        List<List<Integer>> adjacencyListNoCycle = new ArrayList<>();
        adjacencyListNoCycle.add(Arrays.asList(1, 2));          // 0
        adjacencyListNoCycle.add(Arrays.asList(2, 3));          // 1
        adjacencyListNoCycle.add(Arrays.asList(3, 4));          // 2
        adjacencyListNoCycle.add(Collections.emptyList());      // 3
        adjacencyListNoCycle.add(Arrays.asList(4));             // 4 (Disconnected component)

        startTime = System.nanoTime();

        ParallelHamiltonianSearch solverNoCycle =
                new ParallelHamiltonianSearch(adjacencyListNoCycle, threadCount);
        List<Integer> noCycle = solverNoCycle.findHamiltonianCycle(0);

        endTime = System.nanoTime();

        if (noCycle != null) {
            System.out.println("Found Hamiltonian Cycle: " + noCycle);
        } else {
            System.out.println("No Hamiltonian Cycle found");
        }
        System.out.println("Time for Test 2 (no cycle): " + (endTime - startTime) / 1_000_000 + " ms");
    }
}
