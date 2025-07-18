import java.util.*;
import java.util.concurrent.locks.*;

public class Variable {
    private final int id;
    private int value;
    private final List<Variable> inputs;     // Variables this variable depends on
    private final List<Variable> dependents; // Variables that depend on this variable
    private final Lock mutex;

    public Variable(int id) {
        this.id = id;
        this.value = 0;
        this.inputs = new ArrayList<>();
        this.dependents = new ArrayList<>();
        this.mutex = new ReentrantLock();
    }

    public int getId() {
        return id;
    }

    public void addInput(Variable var) {
        inputs.add(var);
        var.addDependent(this);
    }

    public void addDependent(Variable var) {
        dependents.add(var);
    }

    public int getValue() {
        return value;
    }

    public List<Variable> getInputs() {
        return inputs;
    }

    public List<Variable> getDependents() {
        return dependents;
    }

    public Lock getMutex() {
        return mutex;
    }

     // Updates the value of a primary variable and propagates the change to its dependents.
     // This method locks all affected variables in a consistent order to avoid deadlocks.

    public void updatePrimaryValue(int newValue) {
        int delta = newValue - this.value;
        if (delta == 0) return;

        // Collect all affected variables
        Set<Variable> variablesToUpdate = new HashSet<>();
        collectAffectedVariables(variablesToUpdate);

        // Sort variables by ID to ensure consistent locking order
        List<Variable> variableList = new ArrayList<>(variablesToUpdate);
        variableList.sort(Comparator.comparingInt(Variable::getId));

        // Lock all variables in order
        for (Variable var : variableList) {
            var.getMutex().lock();
        }

        try {
            // Map to hold computed deltas for each variable
            Map<Variable, Integer> deltaMap = new HashMap<>();
            deltaMap.put(this, delta);

            // Compute deltas for dependents
            for (Variable var : variableList) {
                if (var == this) continue;
                int varDelta = 0;
                for (Variable input : var.getInputs()) {
                    varDelta += deltaMap.getOrDefault(input, 0);
                }
                deltaMap.put(var, varDelta);
            }

            // Update the values of all variables
            for (Variable var : variableList) {
                int varDelta = deltaMap.getOrDefault(var, 0);
                if (varDelta != 0) {
                    int oldValue = var.value;
                    var.value += varDelta;
                    // Print the modification
                    System.out.printf("Thread %s: Variable %d updated from %d to %d%n",
                            Thread.currentThread().getName(), var.getId(), oldValue, var.value);
                }
            }
        } finally {
            // Unlock all variables in reverse order
            Collections.reverse(variableList);
            for (Variable var : variableList) {
                var.getMutex().unlock();
            }
        }
    }


    //  Recursively collects all variables affected by the update.

    private void collectAffectedVariables(Set<Variable> variables) {
        if (variables.contains(this)) return;
        variables.add(this);
        for (Variable dep : dependents) {
            dep.collectAffectedVariables(variables);
        }
    }
}
