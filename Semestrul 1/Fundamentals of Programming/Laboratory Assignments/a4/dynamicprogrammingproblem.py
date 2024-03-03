#part[i][j] = true if a subset of {arr[0], arr[1], ..arr[i-1]} has sum equal to j, otherwise false
from pprint import pprint
from collections import Counter

#dynamic programming approach

def subsets(arr, n):
    sum = 0
    i, j = 0, 0
    # calculate sum of all elements
    for i in range(n):
        sum = sum + arr[i]


    if sum % 2 != 0:
        print("Can't make two subsets having same sum")
        return False


    part = [[1 for _ in range(sum // 2 + 1)] for _ in range(n + 1)]

    for i in range(1, sum // 2 + 1):
        part[0][i] = 0

    for i in range(n + 1):
        part[i][0] = 1
    pprint(part)



    for i in range(1, n + 1):

        for j in range(1, sum//2 + 1):
            pprint(part)
            print()

            part[i][j] = part[i-1][j]

            if j >= arr[i - 1]:
                part[i][j] = (part[i][j] or part[i - 1][j - arr[i-1]])
    k=sum//2
    if (not part[n][k]):
        print("Can't generate two subsets having same sum")
        return -1
    i=n
    set1=[]
    set2=[]
    while (i > 0 and k >= 0):

        if (part[i-1][k]):
            i =i - 1
            set2.append(arr[i])

        elif (part[i - 1][k - arr[i - 1]]):
            i =i - 1
            k =k - arr[i]
            set1.append(arr[i])
    print(set1)
    print(set2)




#recursive naive implementation

def apelare(num):
    s = sum(num)
    if s % 2 != 0:
        return False

    return apelare_recursiv(num, s / 2, 0)


def apelare_recursiv(num, sum, i):

    if sum == 0:
        return True

    n = len(num)
    if n == 0 or i >= n:
        return False

    if num[i] <= sum:
        set1.append(num[i])
        if(apelare_recursiv(num, sum - num[i], i + 1)):
            return True
    return apelare_recursiv(num, sum, i + 1)


set1= []
A = [5,5,1,10,1]
n = len(A)

if(apelare(A)):
    set1= []
    print("Can make two subsets: " + str(apelare(A)))
    c1 = Counter(set1)
    c2 = Counter(A)
    set2 = list((c2-c1).elements())
    print(set1)
    print(set2)
else:
    print("Can't make two subsets having same sum")



# arr = [1,1,1,5,2,2]
# n = len(arr)
# subsets(arr,n)
# arr = [1,1,2,2,3]
# n = len(arr)
# subsets(arr,n)
# arr = [5,5,1,10,1]
# n = len(arr)
# subsets(arr,n)
# arr = [5, 5, 1, 10, 3]
# n = len(arr)
# subsets(arr,n)

