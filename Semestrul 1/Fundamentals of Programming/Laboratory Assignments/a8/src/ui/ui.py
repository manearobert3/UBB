import unittest

from src.repository.repo import Repo
from src.domain.domain import Student
from src.domain.domain import Assignment

# class TestRepo(unittest.TestCase):
#     def setUp(self):
#         self.test=Repo()
#
#     def test_add(self):
#         result = self.test.add_student(1, 'Andrei', 914)
#         print(result)

class Console:
    def __init__(self, therepo):
        self.__repository = therepo

    def run_menu(self):

        while True:
            print("1.Add student")
            print("2.Remove student")
            print("3.Update student")
            print("4.List students")
            print("5.Add assignment")
            print("6.Remove assignment")
            print("7.Update assignment")
            print("8.List assignment")
            print("9.Exit")
            choice=input("choice=")
            if choice == '1':
                x=input("Id=")
                y=input("name")
                z=input("group")
                self.__repository.add_student(x,y,z)
            elif choice == '2':
                x=input("Id=")
                self.__repository.remove_student(x)
            elif choice == '3':
                x=input("Id=")
                y=input("new name")
                z=input("new group")
                self.__repository.update_student(x,y,z)
            elif choice == '4':
                self.__repository.list_students()
            elif choice == '5':
                x = input("assignment id=")
                y = input("assignment description=")
                z = input("assignment deadline=")
                self.__repository.add_assignment(x,y,z)
            elif choice == '6':
                x = input("assignment id=")
                self.__repository.remove_assignment(x)
            elif choice == '7':
                x = input("assignment id=")
                y = input("new assignment description=")
                z = input("new assignment deadline=")
                self.__repository.update_assignment(x,y,z)
            elif choice == '8':
                self.__repository.list_assignments()
            elif choice == '9':
                exit()
            else:
                print("invalid input")


# unittest.main()
therepo=Repo()
console= Console(therepo)
console.run_menu()