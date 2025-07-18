

class FiniteAutomata:
    def __init__(self):
        self.states = []
        self.alphabet = []
        self.transitions = {}
        self.start_state = 'q0'
        self.final_states = []
        self.read_from_file()

    def parse_transitions(self, line):
        if line.startswith("R"):
            return
        else:
            first_state = line.strip().split(' = ')[0]
            transitions_unprepared = line.strip().split(' = ')[1].split(' > ')
            elements = transitions_unprepared[0]
            elements = elements.split(', ')
            last_state= transitions_unprepared[1]
            if first_state not in self.transitions:
                self.transitions[first_state] = {}
            if last_state not in self.transitions[first_state]:
                self.transitions[first_state][last_state] = []
            for element in elements:
                self.transitions[first_state][last_state].append(element)

    def read_from_file(self):
        f = open("FA.in", "r")
        transitions_read = True
        for line in f:
            if line.startswith("Q"):
                self.states = line.strip().split(': ')[1].split(', ')
            elif line.startswith("E"):
                self.alphabet = line.strip().split(': ')[1].split(', ')
            elif line.startswith("R"):
                self.parse_transitions(line)
            elif line.startswith("F"):
                self.final_states = line.strip().split(': ')[1].split(', ')
            elif transitions_read:
                self.parse_transitions(line)

    def print_menu(self):
        print("1. Display the set of states")
        print("2. Display the alphabet")
        print("3. Display the transitions")
        print("4. Display the final states")
        print("5. Check if a word is accepted by the FA")
        print("0. Exit")

    def menu(self):
        while True:
            self.print_menu()
            option = input("Choose option: ")
            match option:
                case '1':
                    print(self.states)
                case '2':
                    print(self.alphabet)
                case '3':
                    for state in self.transitions:
                        for next_state in self.transitions[state]:
                            letters = self.transitions[state][next_state]
                            print(f"{state}, {letters} -> {next_state}")
                case '4':
                    print(self.final_states)
                case '5':
                    word = input("Enter a word to check: ")
                    if self.check_word(word):
                        print("The word is accepted by the FA.")
                    else:
                        print("The word is not accepted by the FA.")
                case '0':
                    break
                case _:
                    print("Invalid option")

    def check_word(self, word):
        current_state = self.start_state
        for element in word:
            if current_state not in self.transitions:
                return False
            next_state = None
            for state, elements in self.transitions[current_state].items():
                if element in elements:
                    next_state = state
                    break
            if next_state is None:
                return False
            current_state = next_state
        return current_state in self.final_states

