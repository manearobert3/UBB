class Student:
    def __init__(self, student_id, name, group):
        self.student_id = student_id
        self.name = name
        self.group = group

    def get_student_id(self):
        return self.student_id
    def get_name(self):
        return self.name
    def get_group(self):
        return self.group
    def set_student_id(self,new_student_id):
        self.student_id=new_student_id
    def set_name(self,new_name):
        self.name=new_name
    def set_group(self,new_group):
        self.group=new_group


    def __str__(self):
        return f"Student Id: {self.student_id}, Student Name: {self.name}, Student Group: {self.group}"

class Assignment:
    def __init__(self, assignment_id, description, deadline):
        self.assignment_id = assignment_id
        self.description = description
        self.deadline = deadline

    def get_assignment_id(self):
        return self.assignment_id
    def get_description(self):
        return self.description
    def get_deadline(self):
        return self.deadline
    def set_assignment_id(self,new_assignment_id):
        self.assignment_id=new_assignment_id
    def set_description(self,new_description):
        self.description=new_description
    def set_deadline(self,new_deadline):
        self.deadline=new_deadline

    def __str__(self):
        return f"Assignment Id: {self.assignment_id}, description: {self.description}, deadline: {self.deadline}"