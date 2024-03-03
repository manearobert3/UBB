
class Services:
    def __init__(self, repository):
        self.repository = repository
        self.undo_stack = []

    def add_number(self, number):
        self.repository.add_number(number)
    def randomgen(self):
        self.repository.randomgen()
    def get_numbers(self):
        return self.repository.get_numbers()
    def display(self):
        print(self.repository.get_numbers())
    def filter(self, start, end):
        self.repository.filter_numbers(start,end)

    def add_undo(self):
        self.repository.add_undo()
    def undo(self):
        self.repository.undo1()
