from Grammar import Grammar

class Parser:
    @staticmethod
    def read_from_file(filename):
        P={}
        with open(filename, "r") as grammar_file:
            N = Parser.parse_line(grammar_file.readline())
            sigma = Parser.parse_line(grammar_file.readline())
            S = Parser.parse_line(grammar_file.readline())
            grammar_file.readline()
            for line in grammar_file:
                Parser.parse_non_terminals(P, line)
        return Grammar(N, sigma, P, S)

    @staticmethod
    def parse_line(line):
        line = line.strip().split("=>")[1]
        line = line.strip()
        symbols = line.split(" ")
        symbols = list(filter(None, symbols))
        return symbols

    @staticmethod
    def parse_non_terminals(P, line):
        line = line.strip().split("->")
        key = line[0].strip()
        line = line[1].strip()

        line = line.split("|")
        for i in range(len(line)):
            line[i] = line[i].strip()
        
        P[key] = line
        
