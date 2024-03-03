#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#


def inputsomething():
    line= input("Input the command you want: ")
    return line
def verify_day(day):
    try:
        day = int(day)
        if(day < 1 or day > 30):
            raise ValueError
    except ValueError as e:
        print("Day must be a natural number between 1 and 30!")
        return
    return day

def verify_value(value):
    try:
        value = int(value)
        if(value<0):
            raise ValueError("Value must be a positive integer number")
    except ValueError as e:
        raise ValueError("Value must be a natural number!")
    return value

def verify_type(type):
    try:
        type = str(type)
        if (type != 'in' and type !='out') :
            raise TypeError
    except TypeError as e:
        print("The only options for type are only 'in' and 'out'")
        return
    return type

def verify_word(with_word):
    try:
        with_word=str(with_word)
        if(with_word!='with'):
            raise ValueError
    except ValueError as e:
        print("Incorrect syntax for replace transaction")
        return
    return with_word


def start_end(start_day, end_day):
    try:
        if(end_day<start_day):
            raise ValueError
    except ValueError as e:
        print("End Day must be bigger than Start Day")
        return
def print_all(transaction):
    print(transaction)
def printsomething(a):
    print(a)