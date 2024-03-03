#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#

from ui import *
from datetime import date
def create_transaction(day, value, type, description):
    return {"day": day,
            "value": value,
            "type": type,
            "description": description}

def get_transaction_day(transaction):
    return transaction["day"]

def get_transaction_value(transaction):
    return transaction["value"]

def get_transaction_type(transaction):
    return transaction["type"]

def get_transaction_description(transaction):
    return transaction["description"]

def append_to_list(list, dictionary):
    list.append(dictionary)

def set_transaction_day(transaction, day):
    transaction["day"] = day
    return transaction["day"]

def set_transaction_value(transaction, value):
    transaction["value"] = value
    return transaction["value"]

def set_transaction_type(transaction,type):
    transaction["type"] = type
    return transaction["type"]

def set_transaction_description(transaction, description):
    transaction["description"] = description
    return transaction["description"]

def undo(transaction,alltransactions):
    alltransactions.append(transaction)
    return alltransactions


def useundo(transaction,stack):
    # n=len(transaction)
    # i=0
    # while (len(transaction)!=0):
    #         transaction.pop(i)
    # transaction.append(alltransactions[len(alltransactions)-1])
    # return transaction
    if(len(stack)==1):
        return transaction
    else:
        stack.pop()
        transaction[:]=stack[len(stack)-1]
    return transaction

"""
Function random creates a randomly generated list of transactions

"""
def random(transaction):
    desc=['Pizza','Milk','Eggs','Vacation','Fruits','Clothes','Sweets','Gifts','School','Health']
    import random
    for i in range(10):
        day=random.randint(1,30)
        j=random.randint(1,2)
        if(j==1):
            type='in'
        else:
            type='out'
        j=random.randint(0,9)
        description=desc[j]
        value=random.randint(1,9999)
        transaction.append(create_transaction(day,value,type,description))

"""
Function command puts every argument of a given string in 'args'
and the first word from that string of words in 'cmd'
"""
def command():
    line= inputsomething()
    pos = line.find(' ')
    if pos == -1:
        return line, []
    cmd_name = line[:pos]
    args = line[pos+1:]
    args = args.split(' ')
    args = [arg.strip() for arg in args]
    return cmd_name, args

"""
function add_transaction creates a variable 'day' with the current day and 
verifies if all the other parameters given are valid and then 
creates a new dictionary to be appended to the list 'transaction'
"""
def add_transaction(transaction , value, type, description):
    today = date.today()
    day = today.strftime("%d")
    day=int(day)
    verify_value(value)
    verify_type(type)
    value=int(value)
    type=str(type)
    transaction.append(create_transaction(day, value, type, description))
    return transaction
"""
function insert_transaction verifies if all the parameters given are valid and then 
creates a new dictionary to be appended to the list 'transaction'
"""
def insert_transaction(transaction, day, value, type, description):
    verify_day(day)
    verify_value(value)
    verify_type(type)
    day=int(day)
    value=int(value)
    type=str(type)
    transaction.append(create_transaction(day, value, type, description))
    return transaction
"""
function remove_transaction verifies if 'parameter' is a string or integer
and then searches for the correct type inputted in the transaction list and eliminates it

"""
def remove_transaction(transaction,parameter):
    if(parameter.isnumeric()==True):
        parameter=int(parameter)
        verify_day(parameter)
    else:
        verify_type(parameter)
    n=len(transaction)
    i=0
    if type(parameter)==int:
        while(i<len(transaction)):
            if(get_transaction_day(transaction[i])==parameter):
                transaction.pop(i)
                n=n-1
                i=i-1
            i=i+1
    elif type(parameter)==str:
        while (i <len(transaction)):
            if (get_transaction_type(transaction[i]) == parameter):
                transaction.pop(i)
                n = n - 1
                i=i-1
            i = i + 1
    return transaction

"""
Function remove_interval takes input a start_day and an end_day where start_day<end_day
and removes any transaction made between those two days

"""

def remove_interval(transaction, start_day, end_day):
    verify_day(start_day)
    verify_day(end_day)
    start_day=int(start_day)
    end_day=int(end_day)
    start_end(start_day,end_day)


    n = len(transaction)
    i = 0
    while (i < len(transaction)):
        if (get_transaction_day(transaction[i]) < end_day and get_transaction_day(transaction[i]) > start_day ):
            transaction.pop(i)
            n = n - 1
            i=i-1
        i = i + 1
    return transaction

"""
check_option functions verify if the syntax is correct for any of the
'remove', 'list', 'filter' inputs and starts the function accordingly

"""

def check_option_remove(cmd,ars):
    if cmd == 'remove' and 'to' in ars and ars[1]=='to':
        cmd_name='removeinterval'
        ars.pop(1)
        return cmd_name, ars
    elif cmd == 'remove':
        cmd_name='remove'
        return cmd_name, ars
    return cmd,ars

def check_option_list(cmd,ars):
    if len(ars)==0 and cmd=='list':
        cmd='list'
        return cmd, ars
    elif len(ars)==1 and cmd=='list':
        cmd='listtype'
        return cmd, ars
    elif len(ars)==2 and cmd=='list' and 'balance' in ars and ars[0]=='balance':
        cmd='balance'
        ars.pop(0)
        return cmd, ars
    elif len(ars)==2 and cmd=='list' and(ars[0]=='<' or ars[0]=='>' or ars[0]=='='):
        cmd='listcomp'
        return cmd, ars
    try:
        if(len(ars)!=1 and len(ars)!=0 and len(ars)!=2 and cmd=='list'):
            raise TypeError
    except TypeError as e:
        print("Invalid operation")
    return cmd, ars


def check_option_filter(cmd,ars):
    if len(ars)==1 and cmd=='filter':
        cmd='filter'
    elif len(ars)==2 and cmd=='filter':
        cmd='filtervalue'
    return cmd,ars

"""
Function filter eliminates all the elements of transaction if they don't have 
the same type as the one inputted by the user

"""
def filter(transaction,type):
    type = verify_type(type)
    i=0
    n=len(transaction)
    while (i < len(transaction)):
        if (get_transaction_type(transaction[i])!=type):
            transaction.pop(i)
            n = n - 1
            i=i-1
        i = i + 1

"""
Function filtervalue eliminates all the values of a different type to the one inputted by the user
by checking if the two types are equal and the value is smaller than the given value and then using pop function to eliminate the transaction from the initial list

"""
def filtervalue(transaction,type,value):
    verify_value(value)
    verify_type(type)
    type=str(type)
    value=int(value)
    i = 0
    n = len(transaction)
    while (i < len(transaction)):
        if (get_transaction_type(transaction[i])!=type or (get_transaction_value(transaction[i])>=value and get_transaction_type(transaction[i])==type)):
            transaction.pop(i)
            n = n - 1
            i=i-1
        i = i + 1

"""
 Function replace_transaction takes from the user an instruction of form: replace <day> <type> <description> with <value>
 and finds a transaction on the same day as the one inputted, of the same type and description and changes its value to the one inputted

"""
def replace_transaction(transaction, day, type,description, with_word, value):
    verify_word(with_word)
    verify_day(day)
    verify_value(value)
    verify_type(type)
    day=int(day)
    value=int(value)
    type=str(type)
    for i in range(len(transaction)):
        if(get_transaction_day(transaction[i])==day and get_transaction_type(transaction[i])==type and get_transaction_description(transaction[i])==description):
            transaction[i]['value']=set_transaction_value(transaction[i],value)
    return transaction

"""
    Function balance takes a day and sums the value of a transaction if it has 
    the same day as the inputted day and the type = 'in' else it subtracts

"""
def balance(transaction,day):
    day=verify_day(day)
    balance=0
    for i in range(len(transaction)):
        if(get_transaction_day(transaction[i])==day and get_transaction_type(transaction[i])=='in'):
            balance=balance + get_transaction_value(transaction[i])
        elif(get_transaction_day(transaction[i])==day and get_transaction_type(transaction[i])=='out'):
            balance=balance - get_transaction_value(transaction[i])
    printsomething(balance)
    return balance
'''

 Function listcomparison takes a comparison sign given by the user ('<','>','=')
 and a value and compares every case that could exist
 and appends the list element to a new list to print it afterwards

'''
def listcomparison(transaction,comparison_sign,value):
    value=verify_value(value)
    forshow=[]
    for i in range(len(transaction)):
        if comparison_sign=='<' and get_transaction_value(transaction[i])<value:
            forshow.append(transaction[i])
        elif comparison_sign=='>' and get_transaction_value(transaction[i])>value:
            forshow.append(transaction[i])
        elif comparison_sign=='=' and get_transaction_value(transaction[i])==value:
            forshow.append(transaction[i])
    printsomething(forshow)


"""
 Function listtype take as parameters transaction which is the list of all the transactions so far
 and then displays the transactions by appending them to a new list if they have the same type
 as the one inputted by the user
 
"""
def listtype(transaction, type):
    try:
        type = str(type)
        if (type != 'in' and type !='out') :
            raise TypeError
    except TypeError as e:
        print("The only options for type are only 'in' and 'out'")
        return
    forshow=[]
    for i in range(len(transaction)):
        if get_transaction_type(transaction[i])==type:
            forshow.append(transaction[i])
    printsomething(forshow)


def asserting():
    test=[]
    assert(add_transaction(test,100,'out','pizza')==[{'day': 14, 'value': 100, 'type': 'out', 'description': 'pizza'}])
    assert (insert_transaction(test,25, 100, 'out', 'pizza') == [{'day': 14, 'value': 100, 'type': 'out', 'description': 'pizza'}, {'day': 25, 'value': 100, 'type': 'out', 'description': 'pizza'}])
    assert(remove_interval(test,10,15))==[{'day': 25, 'value': 100, 'type': 'out', 'description': 'pizza'}]
    assert(remove_transaction(test,'out')==[])
    add_transaction(test, 100, 'out', 'pizza')
    assert (remove_transaction(test, '14') == [])
    add_transaction(test, 100, 'out', 'pizza')
    assert(replace_transaction(test,14, 'out', 'pizza', 'with', '2000')==[{'day': 14, 'value': 2000, 'type': 'out', 'description': 'pizza'}])