def consistent(x,n):
    s = a[0]
    for i in range(len(x)):
        if (x[i] == 1):
            s = s + a[i + 1]
        else:
            s = s - a[i + 1]
    remsum = 0
    for i in range(len(x) + 1, len(a)):  # the remaining elements in a (the initial array of elements)
        remsum = remsum + abs(a[i])      # sum of the remaining elements in a (the initial array of elements)
    if s + remsum < 0:
        return False
    else:
        return True

def first(x):
    return 0

def next_elem(x, n):
    if x[len(x) - 1] == 1:
        return None
    return x[len(x) - 1] + 1


def is_solution(x,n):
    return len(x)==n


def output_solution(x):
    print(x)

def initial_value():
    return -1



# def back_rec(x, n):
#     for el in range(2):
#         if(len(x) < n):
#             x.append(el)
#             if consistent(x, n):
#                 if is_solution(x, n):
#                     output_solution(x)
#                 else:
#                     back_rec(x[:], n)
#             x.pop()     # removes last item from list

def back_rec(x, n):
    el = first(x)
    x.append(el)
    while el is not None:
        if consistent(x, n):
            if is_solution(x, n):
                output_solution(x)
            else:
                back_rec(x[:], n)
        el = next_elem(x, n)
        x[-1] = el


def back_iter(n):
    x = [initial_value()]
    while len(x) > 0:
        el = next_elem(x, n)
        while el is not None:
            x[-1] = el
            if consistent(x, n):
                if is_solution(x, n):
                    output_solution(x)
                else:
                    x.append(initial_value())
                    break
            el = next_elem(x, n)
        if el is None: x = x[:-1]


n= int(input("insert number n: "))
a=[]
for i in range(0,n):
    l=int(input())
    a.append(l)
print("iterativ:")
back_iter(n-1)
print("recursiv:")
back_rec([], n-1)