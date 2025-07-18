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
            print("6. Print the canonical collection")
            print("7. Exit")
            command = input("enter command: ")
            if command == "1":
                print(grammar.get_N())
            elif command == "2":
                print(grammar.get_Sigma())
            elif command == "3":
                print(grammar.get_P())
            elif command == "4":
                print(grammar.get_S())
            elif command == "5":
                non_terminal = input("Enter non-terminal: ")
                try:
                    print(grammar.get_productions_for_non_terminal(non_terminal))
                except ValueError as ve:
                    print(ve)
            elif command == "6":
                grammar.print_canonical_collection()

            elif command == "7":
                break
            else:
                print("Invalid command")
                break