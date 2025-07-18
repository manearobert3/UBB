class Grammar:
    def __init__(self, N, sigma, P, S):
        self.N = N
        self.Sigma = sigma
        self.P = P
        self.S = S

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
                raise ValueError("Key {key} is not in N".format(key=key))
    
    def check_is_valid_production(self, production):
        production = production.split(" ")
        for symbol in production:
            if symbol not in self.N and symbol not in self.Sigma:
                raise ValueError("Symbol {symbol} is not in N or Sigma".format(symbol=symbol))

    def get_productions_for_non_terminal(self, non_terminal):
        if non_terminal not in self.P:
            raise ValueError("Non-terminal {non_terminal} is not in P".format(non_terminal=non_terminal))
        return self.P[non_terminal]

    def print_grammar(self):
        print("N, set of non terminals = ", self.N)
        print("Sigma, set of terminals = ", self.Sigma)
        print("S, initial state = ", self.S)
        print("P, set of productions = ", self.P)

