package test;

import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ParallelHamiltonianSearchWithThreads {
    // Shared state to indicate that a solution has been found
    private final AtomicBoolean solutionFound = new AtomicBoolean(false);

    // Store the solution here once found
    private volatile List<Integer> solutionPath = null;

    // Graph representation: adjacencyList.get(u) gives the neighbors of u
    private final List<List<Integer>> adjacencyList;
    private final int n; // number of vertices

    public ParallelHamiltonianSearchWithThreads(List<List<Integer>> adjacencyList) {
        this.adjacencyList = adjacencyList;
        this.n = adjacencyList.size();
    }

    /**
     * Attempts to find a Hamiltonian cycle starting from the given start vertex.
     * Returns a list of vertices in order if found, otherwise null.
     */
    public List<Integer> findHamiltonianCycle(int start) {
        boolean[] visited = new boolean[n];
        visited[start] = true;
        List<Integer> path = new ArrayList<>();
        path.add(start);

        // Start the search in the current thread
        search(start, visited, path, start);

        if (solutionFound.get()) {
            return solutionPath;
        } else {
            return null;
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
                solutionPath.add(start);
                solutionFound.set(true);
            }
            return;
        }

        // Explore neighbors of the current vertex
        List<Integer> neighbors = adjacencyList.get(current);
        List<Thread> threads = new ArrayList<>();

        for (int next : neighbors) {
            if (!visited[next] && !solutionFound.get()) {
                boolean[] newVisited = Arrays.copyOf(visited, n);
                newVisited[next] = true;
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(next);

                // Create a new thread to explore this neighbor
                Thread t = new Thread(() -> search(next, newVisited, newPath, start));
                t.start();
                threads.add(t);
            }
        }

        // Wait for all spawned threads to complete
        for (Thread t : threads) {
            if (solutionFound.get()) {
                // If solution already found, we can interrupt waiting threads
                break;
            }
            try {
                t.join();
            } catch (InterruptedException e) {
                // If interrupted, stop
                Thread.currentThread().interrupt();
            }
        }
    }

    // Simple test runner
    public static void main(String[] args) {
        // Test with a graph that has a Hamiltonian cycle
        // Example:
        // 0 -> 1, 2
        // 1 -> 2, 3
        // 2 -> 3, 4
        // 3 -> 0
        // 4 -> 1
        List<List<Integer>> adjacencyListWithCycle = new ArrayList<>();
        adjacencyListWithCycle.add(Arrays.asList(1, 2)); // 0
        adjacencyListWithCycle.add(Arrays.asList(2, 3)); // 1
        adjacencyListWithCycle.add(Arrays.asList(3, 4)); // 2
        adjacencyListWithCycle.add(Arrays.asList(0));    // 3
        adjacencyListWithCycle.add(Arrays.asList(1));    // 4

        ParallelHamiltonianSearchWithThreads solverWithCycle = new ParallelHamiltonianSearchWithThreads(adjacencyListWithCycle);
        List<Integer> cycle = solverWithCycle.findHamiltonianCycle(0);
        if (cycle != null) {
            System.out.println("Found Hamiltonian cycle: " + cycle);
        } else {
            System.out.println("No Hamiltonian cycle found in the first test graph.");
        }

        // Test with a graph that does NOT have a Hamiltonian cycle
        // Example:
        // 0 -> 1
        // 1 -> 2
        // 2 -> 3
        // 3 -> (no outgoing edges)
        // No way to return back to 0 or cover all vertices in a cycle
        List<List<Integer>> adjacencyListNoCycle = new ArrayList<>();
        adjacencyListNoCycle.add(Arrays.asList(1));    // 0
        adjacencyListNoCycle.add(Arrays.asList(2));    // 1
        adjacencyListNoCycle.add(Arrays.asList(3));    // 2
        adjacencyListNoCycle.add(Collections.emptyList()); // 3

        ParallelHamiltonianSearchWithThreads solverNoCycle = new ParallelHamiltonianSearchWithThreads(adjacencyListNoCycle);
        List<Integer> noCycle = solverNoCycle.findHamiltonianCycle(0);
        if (noCycle != null) {
            System.out.println("Found Hamiltonian cycle (unexpected): " + noCycle);
        } else {
            System.out.println("No Hamiltonian cycle found in the second test graph, as expected.");
        }
    }
}
