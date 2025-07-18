class Grammar:
    def __init__(self, N, sigma, P, S):
        self.N = N  # Non-terminals
        self.Sigma = sigma  # Terminals
        self.P = P  # Productions (dictionary: key -> list of productions)
        self.S = S  # Start symbol

    def get_N(self):
        return self.N

    def get_Sigma(self):
        return self.Sigma

    def get_P(self):
        return self.P

    def get_S(self):
        return self.S

    def check_is_valid(self):
        self.check_is_CFG()
        for key in self.P.keys():
            for production in self.P[key]:
                self.check_is_valid_production(production)

    def check_is_CFG(self):
        for key in self.P.keys():
            if key not in self.N:
                raise ValueError(f"Key {key} is not in N")

    def check_is_valid_production(self, production):
        production = production.split(" ")
        for symbol in production:
            if symbol not in self.N and symbol not in self.Sigma:
                raise ValueError(f"Symbol {symbol} is not in N or Sigma")

    def get_productions_for_non_terminal(self, non_terminal):
        if non_terminal not in self.P:
            raise ValueError(f"Non-terminal {non_terminal} is not in P")
        return self.P[non_terminal]

    def print_grammar(self):
        print("N, set of non terminals = ", self.N)
        print("Sigma, set of terminals = ", self.Sigma)
        print("S, initial state = ", self.S)
        print("P, set of productions = ", self.P)

    def closure(self, items):
        closure_list = list(items)
        added = True

        while added:
            added = False
            new_items = []
            for item in closure_list:
                _, body, dot_index = item
                # If the dot is before a non-terminal, expand the closure
                if dot_index < len(body) and body[dot_index] in self.N:
                    non_terminal = body[dot_index]
                    # Add all productions for the non-terminal
                    for production in self.get_productions_for_non_terminal(non_terminal):
                        new_item = (non_terminal, tuple(production.split(" ")), 0)
                        # Add new items only if they aren't already in the closure
                        if new_item not in closure_list and new_item not in new_items:
                            new_items.append(new_item)
                            added = True
            # Extend the closure list with the new items
            closure_list.extend(new_items)

        return closure_list

    def goto(self, items, symbol):
        goto_list = []
        for item in items:
            head, body, dot_index = item
            # Check if the dot is before the specified symbol
            if dot_index < len(body) and body[dot_index] == symbol:
                new_item = (head, body, dot_index + 1)  # Move the dot one step to the right
                if new_item not in goto_list:
                    goto_list.append(new_item)
        return self.closure(goto_list)

    def canonical_collection(self):
        # Start with the initial item for the augmented grammar
        start_item = (f"{self.S}'", (self.S,), 0) # Body is a tuple
        initial_state = self.closure([start_item]) # Compute closure of the start item
        states = [initial_state] # List to store all states (ordered)
        transitions = {} # Dictionary to store transitions (state, symbol -> next state)

        added = True
        while added:
            added = False
            for state in states:
                for symbol in self.N + self.Sigma:
                    next_state = self.goto(state, symbol)
                    # Add the new state if it is not already in the states list
                    if next_state and next_state not in states:
                        states.append(next_state)
                        transitions[(tuple(state), symbol)] = next_state
                        added = True

        return states, transitions

    def print_canonical_collection(self):
        states, transitions = self.canonical_collection()

        # Print states
        print("\nCanonical States:")
        for i, state in enumerate(states):
            print(f"State {i}:")
            for item in state:
                head, body, dot_index = item
                production = " ".join(body[:dot_index]) + " • " + " ".join(body[dot_index:])
                print(f"{head} -> {production}")

        # Print transitions
        print("\nTransitions:")
        for (state, symbol), target_state in transitions.items():
            print(f"From state {state} on symbol {symbol} -> {target_state}")