import random
from src.domain.domain import Domain
class MemoryRepository:
    def __init__(self):
        self.numbers=[]
        self.undo =[]
        self.add_undo()

    """
    :parameter number : is the complex number formed in the domain class
    it gets add to the self.numbers list
    """
    def add_number(self, number):
        self.numbers.append(number)

    """
    get_number returns the list self.numbers
    """

    def get_numbers(self):
        print(self.undo)
        return self.numbers



    """
    function to generate 10 random complex numbers and add them to the list
    """

    def randomgen(self):
        l=[]
        for i in range(10):
            a=random.randint(-100,100)
            b=random.randint(-100,100)
            number=str(Domain(a,b))
            l.append(number)
        self.numbers=l
        self.undo.append(l[:])
    def filter_numbers(self, start, end):
        self.numbers= self.numbers[(start-1):end]

    # adds the list of numbers to the undo stack

    def add_undo(self):
        self.undo.append(self.numbers[:])
    # adds the last item from the undo stack to the main list
    def undo1(self):
        if(len(self.undo)>2):
            self.undo.pop()
            self.numbers=[]
            self.numbers=self.undo[len(self.undo)-1]
        else:
            print("There are not any instructions left to be undone")


