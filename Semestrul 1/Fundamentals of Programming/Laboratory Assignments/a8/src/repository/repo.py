from src.domain.domain import Student
from src.domain.domain import Assignment

class Repo:
    def __init__(self):
        self.students = {}
        self.assignments = {}
        self.grades = {}

    #method add_student adds a student by student_id, name, group
    def add_student(self, student_id, name, group):
        student = Student(student_id, name, group)
        self.students[student_id] = student
        print("Student added.")

    # method remove_student removes a student from the set
    def remove_student(self, student_id):
        student = self.students.pop(student_id, None)
        if student:
            print("Student removed.")
        else:
            print("There are no students with that id.")

    #method update_student takes param: student_id, name, group
    #and modifies the existing name and group with name, group
    def update_student(self, student_id, name, group):
        student = self.students.get(student_id)
        if student:
            student.name = name
            student.group = group
            print("Student updated.")
        else:
            print("There are no students with that id")

    #method list_students prints all the students if therer are any
    def list_students(self):
        if self.students:
            for student in self.students.values():
                print(student)
        else:
            print("There are no students")

    #add_assignment adds a new assignment with the given param assignmend_id, description, deadline

    def add_assignment(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        self.assignments[assignment_id] = assignment

    #remove_assignment removes assignment with the given assignment_id

    def remove_assignment(self, assignment_id):
        assignment = self.assignments.pop(assignment_id, None)
        if assignment:
            print("Assignment removed.")
        else:
            print("There are no assignments.")

    #update_assignment updates an existing assignment given by the assignment_id and updates its description and deadline
    def update_assignment(self, assignment_id, description, deadline):
        assignment = self.assignments.get(assignment_id)
        if assignment:
            assignment.description = description
            assignment.deadline = deadline

    def list_assignments(self):
        if self.assignments:
            for assignment in self.assignments.values():
                print(assignment)
        else:
            print("There are no assignments.")