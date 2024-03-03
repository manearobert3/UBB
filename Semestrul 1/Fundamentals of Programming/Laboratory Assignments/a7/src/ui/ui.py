from src.services.services import Services
from src.repository.repository import MemoryRepository
from src.repository.textfilerepo import TextFileRepository
from src.domain.domain import Domain
class Console:
    def __init__(self,therepo):
        self.__repository= therepo

    '''
    Choose_repo is a function that helps us choose
    the repo to be used in the application
    
    '''

    @staticmethod
    def choose_repo():
        print("Choose Repo type:")
        print("1.Memory Repository")
        print("2.Text File Repository")
        choice = input("Enter your choice")
        if choice == '1':
            repo = MemoryRepository() #this is the memory repository
            return repo
        elif choice == '2':
            repo=TextFileRepository() #this is the text file repository
            return repo
        else:
            print("choice is not valid")
    def menu(self):
        self.__repository.randomgen() # here we generate 10 random instances
        while True:
            print("1.Add a number")
            print("2.Display the list of numbers")
            print("3.Filter the list")
            print("4.Undo")
            print("5.Exit")
            choice= input("enter number from 1 to 5")
            if choice == '1':
                while True:
                    try:
                        a = int(input("a :"))
                        b = int(input("b :"))
                        break
                    except ValueError:
                        print("The input is not a valid int.")
                number=str(Domain(a,b))
                self.__repository.add_number(number)  # function to add a number
                self.__repository.add_undo()  # function to add to the undo stack
            elif choice == '2':
                self.__repository.display()  # here we display the list of numbers
            elif choice == '3':
                while True:
                    try:
                        start = int(input("Input the starting point :"))
                        end =int(input("Input the ending point :"))
                        if(start>end):
                            print("The start value can't be bigger than the end value")
                        else:
                            break
                    except ValueError:
                        print("The input is not a valid int.")

                self.__repository.filter(start,end)   # filter the list of numbers
                self.__repository.add_undo() #again add to the undo stack
            elif choice == '4':
                self.__repository.undo()  # here we call the undo function
            elif choice == '5':
                exit()  #we exit the program
            else:
                print("Inputted command is not valid")

# function for tests
def Test():
    number=Domain('7','9')
    assert(str(number)=='7 + 9i')
    assert(number.get_real()=='7')
    assert (number.get_imag() == '9')

Test()
repo=None
while repo==None:
    repo=Console.choose_repo()
repoo=Services(repo)
a = Console(repoo)
a.menu()