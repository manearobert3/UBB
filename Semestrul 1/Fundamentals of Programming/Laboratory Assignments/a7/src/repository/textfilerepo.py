import os
import random
from src.domain.domain import Domain
class TextFileRepository:
    def __init__(self):
        self.undo = []
        # we initialize the list with the contents of the text file
        if os.path.exists("numbers.txt"):
            with open('numbers.txt','r') as f:
                self.numbers = f.readlines()
                self.numbers = [number.strip() for number in self.numbers]
                # self.add_undo()
        else:
            print("There is no such file")
        # add the list to the undo stack
        self.add_undo()

    '''
    function to generate 10 random complex numbers and add them to the text file
    '''
    def randomgen(self):
        a = random.randint(-100, 100)
        b = random.randint(-100, 100)
        number = str(Domain(a, b))
        with open('numbers.txt', 'w') as f:
            f.write(number + '\n')
        for i in range(9):
            a=random.randint(-100,100)
            b=random.randint(-100,100)
            number=str(Domain(a,b))
            with open('numbers.txt', 'a') as f:
                f.write(number + '\n')


     # """
     # number: is the complex number given in the ui function formed in the domain class
     # add_number adds a number to the text file and list
     # """


    def add_number(self,number):
        with open('numbers.txt', 'a') as f:
            f.write(number + '\n')
        self.numbers.append(number)

    """
    get_number returns the list self.numbers
    """

    def get_numbers(self):
        return self.numbers

    """
    :param: start is the starting point for the filter function
    :param: end is the ending point for the filter function
    this function clears the text file then append the list with just the elements between start and end
    """
    def filter_numbers(self, start, end):
        with open("numbers.txt", "w") as f:
            f.truncate()
        self.numbers=self.numbers[(start-1):end]
        with open("numbers.txt", "w") as f:
            for s in self.numbers:
                f.write(s + "\n")
    # adding the list to the undo stack
    def add_undo(self):
        self.undo.append(self.numbers[:])
    # undo1 gets the last list form the list undo
    # and clears the self.number and adds in it the last item of self.undo
    def undo1(self):
        if(len(self.undo)>1):
            self.undo.pop()
            self.numbers=[]
            self.numbers=self.undo[len(self.undo)-1]
            with open("numbers.txt", "w") as f:
                f.truncate()
                for s in self.undo[len(self.undo)-1]:
                    f.write(s + "\n")
        else:
            print("There are not any instructions left to be undone")


