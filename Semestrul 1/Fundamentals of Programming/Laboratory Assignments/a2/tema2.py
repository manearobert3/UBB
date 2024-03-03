
# import random : Generates a random number between a given positive range.

import random

"""

    The run_menu() function has 4 different options
    from which the user can choose continuously,
    one of the options ends the loop and closes the program.
    
"""

def run_menu():
    a=[]
    while True:
        print_menu()
        x = input("Insert the option number:")
        if x == '1':
            a = create(a)
            print (a)
        elif x == '2':
            step = int(input("Insert the step number:"))
            a = Permutation_Sort(a, step)
            print("The final sorted list is: ")
            print(a)
        elif x == '3':
            step = int(input("Insert the step number:"))
            a = Gnome_Sort(a, len(a), step)
            print("The final sorted list is: ")
            print(a)
        elif x == '4':
            print("Goodbye, user!")
            return False
        else:
            print("Invalid command")

# The function print_menu() prints the options from which the user can choose.

def print_menu():
    print("1: Generate a list of 'n' random  natural numbers")
    print('2: Sort the list by using the Permutation Sort')
    print('3: Sort the list by using the Gnome Sort')
    print('4: Exit')

# The create() function generates a random list of n values (n being given in the console by the user).

def create(a):
    n = int(input("Insert the number of values in the array (insert an integer):"))
    a=[]
    for i in range(0, n):
        b = random.randint(0, 100)
        a.append(b)
    return a

"""
    
    The Permutation_Sort() function sorts a list by trying
    random permutations of the list until it is in the correct order.
    It is a very inefficient sort that is why it is also known as slow sort.

"""

def Permutation_Sort(arr,step):
    k=0
    if  step <1:
        print("The step given is not valid")
    while (is_sorted(arr) == False):
        shuffle(arr)
        k=k+1
        if k % step == 0:
            print("The step number at which the algorithm is at the moment is ", k, ":")
            print(arr)
    if step > k:
        print("The step given is bigger than the amount of steps the algorithm makes.")
    return arr

# The is_sorted() function checks if the list is sorted or not.

def is_sorted(arr):
    n = len(arr)
    for i in range(0, n-1):
        if (arr[i] > arr[i+1]):
            return False
    return True

# The shuffle() function generates a permutation of the list.

def shuffle(a):
    n = len(a)
    for i in range(0, n):
        r = random.randint(0, n-1)
        a[i], a[r] = a[r], a[i]

"""
    
    A function to sort the given list using Gnome sort.
    Gnome Sort is based on the concept of a garden gnome
    who sorts his flower pots this way:
    
    *  The gnome looks at the flower pots, the one next to him 
    and the previous one, he swaps them if they are not arranged properly
    and steps one pot backwards, if the flower pots are in good order
    he steps one pot forward
    
    *   If he is at the start, he steps one pot forward and
    if he is at the last pot he is done.

"""

def Gnome_Sort(arr, n,step):
    k = 0
    if step < 1:
        print("The step given is not valid")
    i = 0
    while i < n:
        k = k + 1
        if i == 0:
            i = i + 1
        if arr[i] >= arr[i - 1]:
            i = i + 1
        else:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            i = i - 1
        if k % step == 0:
            print("The step number at which the algorithm is at the moment is ", k, ":")
            print(arr)
    if step > k:
        print("The step given is bigger than the amount of steps the algorithm makes.")
    return arr

# Main code

run_menu()