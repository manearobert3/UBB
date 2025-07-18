from Parser import Parser
import sys

if __name__ == '__main__':
    if len(sys.argv) != 2:
        filename = input("Enter filename: ")
    else:
        filename = sys.argv[1]
    try:
        with open(filename, "r") as file:
            pass
    except FileNotFoundError as fnfe:
        print(fnfe)
        exit(1)
    grammar = Parser.read_from_file(filename)
    try:
        grammar.check_is_valid()
        print("Grammar is valid")
    except ValueError as ve:
        print(ve)
    else:
        while True:
            print("1. Print the set of non-terminals")
            print("2. Print the set of terminals")
            print("3. Print the set of productions")
            print("4. Print the initial state")
            print("5. Print the productions for a given non-terminal")
            print("6. Exit")
            command = input("Enter command: ")
            match command:
                case "1":
                    print(grammar.get_N())
                case "2":
                    print(grammar.get_Sigma())
                case "3":
                    print(grammar.get_P())
                case "4":
                    print(grammar.get_S())
                case "5":
                    non_terminal = input("Enter non-terminal: ")
                    try:
                        print(grammar.get_productions_for_non_terminal(non_terminal))
                    except ValueError as ve:
                        print(ve)
                case "6":
                    break
                case _:
                    print("Invalid command")
                    break