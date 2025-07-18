import java.util.*;

public class VariableSystem {
    private final Map<Integer, Variable> variables;

    public VariableSystem() {
        variables = new HashMap<>();
    }

    public Variable createVariable(int id) {
        Variable var = new Variable(id);
        variables.put(id, var);
        return var;
    }

    public Variable getVariable(int id) {
        return variables.get(id);
    }

    public Collection<Variable> getAllVariables() {
        return variables.values();
    }

     // Performs a consistency check to ensure all secondary variables correctly sum their inputs.
     // It also prints out the details of each variable being checked.

    public boolean checkConsistency() {
        boolean consistent = true;
        for (Variable var : variables.values()) {
            if (!var.getInputs().isEmpty()) {
                int expectedValue = 0;
                StringBuilder inputsInfo = new StringBuilder();
                for (Variable input : var.getInputs()) {
                    expectedValue += input.getValue();
                    inputsInfo.append(String.format("Input Var %d: %d, ", input.getId(), input.getValue()));
                }

                // Remove trailing comma and space
                if (inputsInfo.length() >= 2) {
                    inputsInfo.setLength(inputsInfo.length() - 2);
                }

                System.out.println(String.format("Checking Variable %d: Value=%d, Expected Sum=%d", var.getId(), var.getValue(), expectedValue));
                System.out.println("  " + inputsInfo.toString());

                if (var.getValue() != expectedValue) {
                    System.out.println("  Inconsistency found!");
                    consistent = false;
                } else {
                    System.out.println("  Variable is consistent.");
                }
            }
        }
        return consistent;
    }
}
