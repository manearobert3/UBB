package test;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ParallelHamiltonianSearch {
    // Shared state to indicate that a solution has been found
    private final AtomicBoolean solutionFound = new AtomicBoolean(false);

    // Store the solution here once found
    private volatile List<Integer> solutionPath = null;

    // Executor service for parallel tasks
    private final ExecutorService executor;

    // Graph representation
    // adjacencyList.get(u) is a list of vertices that u points to
    private final List<List<Integer>> adjacencyList;
    private final int n; // number of vertices

    public ParallelHamiltonianSearch(List<List<Integer>> adjacencyList) {
        this.adjacencyList = adjacencyList;
        this.n = adjacencyList.size();
        // Create a fixed thread pool (e.g., number of processors)
        // You can adjust the pool size as needed.
        this.executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    }

    /**
     * Attempts to find a Hamiltonian cycle starting from the given start vertex.
     * Returns a list of vertices in order if found, otherwise null.
     */
    public List<Integer> findHamiltonianCycle(int start) {
        // The path starts with the starting vertex
        List<Integer> path = new ArrayList<>();
        path.add(start);

        // visited array for tracking visited vertices
        boolean[] visited = new boolean[n];
        visited[start] = true;

        // Start the search
        Future<?> future = executor.submit(() -> search(start, visited, path, start));
        try {
            // Wait for completion or solution found
            future.get();
        } catch (InterruptedException | ExecutionException e) {
            // In a real application, handle properly
            e.printStackTrace();
        }

        // Shutdown the executor
        executor.shutdownNow();

        if (solutionFound.get()) {
            return solutionPath;
        } else {
            return null; // no solution found
        }
    }

    /**
     * Recursive backtracking search to find a Hamiltonian cycle.
     * @param current The current vertex
     * @param visited Visited array
     * @param path Current path
     * @param start The start vertex (for checking cycle completion)
     */
    private void search(int current, boolean[] visited, List<Integer> path, int start) {
        // If a solution is already found by another thread, stop immediately.
        if (solutionFound.get()) {
            return;
        }

        // If we have visited all vertices once, check if there's an edge back to start
        if (path.size() == n) {
            // Check if there's a direct edge to start to form a cycle
            if (adjacencyList.get(current).contains(start)) {
                // Found a Hamiltonian cycle
                solutionPath = new ArrayList<>(path);
                solutionPath.add(start); // Add start at the end to show the cycle
                solutionFound.set(true);
            }
            return;
        }

        // Explore neighbors of the current vertex
        List<Integer> neighbors = adjacencyList.get(current);

        // We'll branch out the search in parallel for each neighbor not visited yet
        List<Callable<Void>> tasks = new ArrayList<>();

        for (int next : neighbors) {
            if (!visited[next]) {
                // If already found a solution, break early
                if (solutionFound.get()) {
                    break;
                }

                boolean[] newVisited = Arrays.copyOf(visited, n);
                newVisited[next] = true;
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(next);

                // Create a task for this branch
                tasks.add(() -> {
                    search(next, newVisited, newPath, start);
                    return null;
                });
            }
        }

        if (!tasks.isEmpty()) {
            // Submit all tasks in parallel
            try {
                // invokeAll will block until all tasks are done
                // However, tasks themselves stop early if solutionFound is set.
                executor.invokeAll(tasks);
            } catch (InterruptedException e) {
                // If interrupted, just return.
            }
        }
    }

    public static void main(String[] args) {
        // Example usage:
        // Suppose we have a directed graph of 5 vertices (0 to 4)
        // We define edges as adjacency list:
        List<List<Integer>> adjacencyList = new ArrayList<>();
        // Vertex 0 -> 1, 2
        adjacencyList.add(Arrays.asList(1, 2));
        // Vertex 1 -> 2, 3
        adjacencyList.add(Arrays.asList(2, 3));
        // Vertex 2 -> 3, 4
        adjacencyList.add(Arrays.asList(3, 4));
        // Vertex 3 -> 0
        adjacencyList.add(Arrays.asList(0));
        // Vertex 4 -> 1
        adjacencyList.add(Arrays.asList(1));

        ParallelHamiltonianSearch solver = new ParallelHamiltonianSearch(adjacencyList);
        List<Integer> cycle = solver.findHamiltonianCycle(0);

        if (cycle != null) {
            System.out.println("Hamiltonian cycle found: " + cycle);
        } else {
            System.out.println("No Hamiltonian cycle found.");
        }
    }
}
