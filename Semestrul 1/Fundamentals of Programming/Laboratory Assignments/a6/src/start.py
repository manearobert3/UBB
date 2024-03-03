#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
# def add_transaction(day, value, type, description):
#     transaction.append(create_transaction(day, value, type, description))
from datetime import date
from functions import *
def solve():
    stack=[]
    transaction=[]
    #random(transaction)
    opt = {"add": add_transaction,
           "list": print_all,
           "insert": insert_transaction,
           "remove": remove_transaction,
           "removeinterval": remove_interval,
           "replace": replace_transaction,
           "filter":filter,
           "filtervalue":filtervalue,
           "balance":balance,
           "listcomp":listcomparison,
           "listtype":listtype,
           "undo":useundo
        }
    while True:
        cmd, ars = command()
        if(cmd=='remove'):
            cmd, ars = check_option_remove(cmd,ars)
        elif(cmd=='filter'):
            cmd, ars=check_option_filter(cmd,ars)
        elif (cmd == 'list'):
            cmd, ars=check_option_list(cmd,ars)
        if (cmd == 'undo' and ars == []):
            transaction=useundo(transaction, stack)
        else:
            try:
                opt[cmd](transaction, *ars)
            except ValueError as e:
                print(e)
            except KeyError as e:
                print("Option not yet implemented", e)
            except TypeError as e:
                print("Option not valid or not yet implemented:", e)
            if(cmd=='add' or cmd=='remove' or cmd =='replace' or cmd=='filter' or cmd=='insert'):
                    copy=transaction.copy()
                    stack.append(copy)


solve()