
from FiniteAutomata import FiniteAutomata
from SymbolTables import SymTblConst, SymTblIdentifier


class Parser:
    CONSTANT_STARTERS = ['\'', '\"']
    OPERATORS = ['<', '>', '=', '!']
    KEYWORDS = ['compl']

    def __init__(self):
        self.tokens = []
        self.constants = SymTblConst()
        self.identifier = SymTblIdentifier()
        self.pif = []
        self.read_from_token()
        self.fa = FiniteAutomata()

    def read_from_token(self):
        with open("token.in", "r") as tokens_file:
            for line in tokens_file:
                self.tokens.append(line.strip())

    def analyze_line(self, line):
        token_list = []
        i = 0
        while i < len(line):
            if line[i].isalnum() or line[i] == '_':
                token = ""
                while i < len(line) and (line[i].isalnum() or line[i] == '_'):
                    token += line[i]
                    i += 1
                token_list.append(token)
            elif line[i] in self.CONSTANT_STARTERS:
                first_char = line[i]
                token = line[i]
                i += 1
                while i < len(line) and line[i] != first_char:
                    token += line[i]
                    i += 1
                if i < len(line):
                    token += line[i]
                    i += 1
                token_list.append(token)
            elif line[i] in self.OPERATORS:
                token = ""
                while i < len(line) and line[i] in self.OPERATORS:
                    token += line[i]
                    i += 1
                token_list.append(token)
            elif line[i] == '#':
                return token_list
            elif line[i] != ' ':
                token_list.append(line[i])
                i += 1
            else:
                i += 1
        return token_list

    def scanner_algorithm(self, line):
        token_list = self.analyze_line(line.strip())
        for token in token_list:
            if token in self.tokens or token in self.KEYWORDS:
                self.pif.append([token, [0, 0]])
            elif self.isIdentifier(token):
                self.identifier.insert_identifier(token)
                self.pif.append(["identifier", self.identifier.get_identifier(token)])
            elif self.isConstant(token):
                self.constants.insert_const(token)
                self.pif.append(["constant", self.constants.get_const(token)])
            else:
                raise Exception(token)

    def _write_to_file(self, filename, content):
        with open(filename, 'w') as file:
            for item in content:
                file.write(f"{item}\n")

    def parse_file(self, filename):
        with open(filename, "r") as file:
            for line_number, line in enumerate(file, start=1):
                try:
                    self.scanner_algorithm(line.strip())
                except Exception as e:
                    print(f"Invalid token {e} at line {line_number}!")
                    return
        print(f"Lexically correct!")

        self._output_results()

    def _output_results(self):
        self.constants.print_table()
        self._write_to_file('PIF.out', self.pif)
        self._write_to_file("CONSTANTS.out", [self.constants.print_table()])
        self._write_to_file("IDENTIFIERS.out", [self.identifier.print_table()])

    def isIdentifier(self, token):
        if any(char.isalpha() for char in token):
            return self.fa.check_word(token)
        return False

    def isConstant(self, token):
        return self.fa.check_word(token)