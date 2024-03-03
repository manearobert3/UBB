#
# Write the implementation for A5 in this file
#
import math
#
# Write below this comment
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values

# def create_complex_number(real, imag):
#     return [real, imag]
#
# def create(list, a,b):
#     list.append([a,b])
#
# def get_real(element):
#     return int(element[0])
#
# def get_imag(element):
#     return int(element[1])
#
# def input_numb(n,a):
#     for i in range(n):
#         c1=create_complex_number(input(),input())
#         create(a, get_real(c1),get_imag(c1))


#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values

def create(list, a):
    list.append(a)

def create_complex_number(real, imag):
    return {'real': real, 'imag': imag}


def get_real(c):
    return int(c['real'])


def get_imag(c):
    return int(c['imag'])

def input_numb(n,a):
    for i in range(n):
        c1=create_complex_number(input(),input())
        create(a, c1)


#
# Write below this comment
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

# Modulus functions computes the modulus of a complex number
def modulus(x,n,a):
    x=[]
    for i in range(n):
        b=math.sqrt(get_real(a[i])*get_real(a[i])+get_imag(a[i])*get_imag(a[i]))
        if(b >= 0 and b<=10):
            x.append(a[i])
    return x

#longsubsequence_list computes the longest alternating subsequence considering each number's real part
def longsubsequence_list(x, n):
    v = []
    # If the number of elements is 0 then we return an empty list
    if(n==0):
        return v
    # If the number of elements is 1 then we return the only element
    if(len(x)==1):
        v.append(get.real(x[0]))
        return v
    # We initialise a matrix with 0
    m = [[0 for i in range(2)]
           for j in range(n)]

    # Initialize all values from 1
    for i in range(n):
        m[i][0], m[i][1] = 1, 1

    res = 1
    # We test if the sequence and add 1 to the matrix accordingly
    for i in range(1, n):
        for j in range(0, i):
            if (get_real(x[j]) < get_real(x[i]) and m[i][0] < m[j][1] + 1):
                m[i][0] = m[j][1] + 1

            if (get_real(x[j]) > get_real(x[i]) and
                    m[i][1] < m[j][0] + 1):
                m[i][1] = m[j][0] + 1

        if (res < max(m[i][0], m[i][1])):
            res = max(m[i][0], m[i][1])
    # Search for one single longest subsequence
    k=res
    if get_real(x[0]) < get_real(x[1]) :
        ok = 1
    if get_real(x[0])> get_real(x[1]) :
        ok = 0
    v.append(get_real(x[0]))
    v.append(get_real(x[1]))
    for i in range(1,n):
        if(get_real(x[i-1])<get_real(x[i]) and ok==0):
            ok=1
            v.append(get_real(x[i]))
            k =k-1
        if(get_real(x[i-1])>get_real(x[i]) and ok==1):
            ok=0
            v.append(get_real(x[i]))
            k =k-1
        if(k==0):
            break
    return v





#
# Write below this comment
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

#printresultslist prints the longest alternating subsequence
def printresultslist(a,n):
    v=longsubsequence_list(a, n)
    print("Elements of the longest alternating subsequence is", v, "and the length:", len(v))


#printmoduluslist prints the list of complex numbers' parts that have the modulus between 0 and 10
def printmoduluslist(x,n,a):
    x=modulus(x,n,a)
    print("Length and elements of a longest subarray of numbers where each number's modulus is in the [0, 10] range are:")
    print("Length: ", len(x), " and elements: ", x)

#print_list prints the list in a " a + b i " way
def print_list(x,n):
    print("The list of complex numbers is:")
    for i in range(n):
        if(int(get_imag(x[i]))<0):
            print(get_real(x[i]),'-',abs(int(get_imag(x[i]))),'i')
        elif (int(get_imag(x[i]))>0):
            print(get_real(x[i]),'+',get_imag(x[i]),'i')

# Input the number of elements
def input_n(n):
    n = int(input("n="))
    return n


# Print the options the user has
def print_menu():
    print("1: Read a list of 'n' complex numbers (in z = 'a+bj' form) from the console:")
    print('2: Display the entire list of numbers on the console')
    print("3: Display: Length and elements of a longest subarray of numbers where each number's modulus is in the [0, 10] range.\n And the the length and elements of a longest alternating subsequence, when considering each number's real part")
    print('4: Exit')

# The main program
def run_menu():
    x = []
    a = []
    n=0
    while True:
        print_menu()
        x1 = input("Insert the option number:")
        if x1 == '1':
            n=input_n(n)
            x = []
            a = []
            input_numb(n,a)
        elif x1 == '2':
            print_list(a,n)
        elif x1 == '3':
            printmoduluslist(x,n,a)
            printresultslist(a,n)
        elif x1 == '4':
            print("Goodbye, user!")
            return False
        else:
            print("Invalid command")
run_menu()


