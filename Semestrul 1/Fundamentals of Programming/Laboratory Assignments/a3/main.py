import random
import timeit
from texttable import Texttable


def build_result_table():
    table = Texttable()
    table.add_row(['Term', 'Best Gnome Sort', 'Worst Gnome Sort', 'Average Gnome Sort'])
    for term in [500, 1000, 2000, 4000, 8000]:
        arr = already_sorted_data(term)
        start_iter = timeit.default_timer()
        row = Gnome_Sort(arr)
        end_iter = timeit.default_timer()
        arr = []
        arr = sorted_in_reverse_data(term)
        start_rec = timeit.default_timer()
        row = Gnome_Sort(arr)
        end_rec = timeit.default_timer()
        arr = []
        arr = random_data(term)
        start_bos = timeit.default_timer()
        row = Gnome_Sort(arr)
        end_bos = timeit.default_timer()
        table.add_row([term, (end_iter - start_iter), (end_rec - start_rec), (end_bos - start_bos)])
    return table


def build_result_table1():
    table = Texttable()
    table.add_row(['Term', 'Best P_S', 'Worst P_S', 'Average P_S'])
    for term in [6, 7, 8, 9, 10]:
        arr = []
        arr = already_sorted_data(term)
        start_ps1 = timeit.default_timer()
        for p in permutation(arr):
            if (is_sorted(p) == True):
                break
        end_ps1 = timeit.default_timer()
        arr = []
        arr = sorted_in_reverse_data(term)
        start_ps2 = timeit.default_timer()
        for p in permutation(arr):
            if (is_sorted(p) == True):
                break
        end_ps2 = timeit.default_timer()
        arr = []
        arr = random_data(term)
        start_ps3 = timeit.default_timer()
        for p in permutation(arr):
            if (is_sorted(p) == True):
                break
        end_ps3 = timeit.default_timer()

        table.add_row([term, (end_ps1 - start_ps1), (end_ps2 - start_ps2), (end_ps3 - start_ps3)])
    return table


def already_sorted_data(data_size):
    result = list(range(0, data_size))
    return result


def sorted_in_reverse_data(data_size):
    result = list(range(data_size, 0, -1))
    return result


def random_data(data_size):
    result = list(range(0, data_size))
    random.shuffle(result)
    return result


def Gnome_Sort(arr):
    i = 0
    n = len(arr)
    while i < n:
        if i == 0:
            i = i + 1
        if arr[i] >= arr[i - 1]:
            i = i + 1
        else:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            i = i - 1
    return arr


def Permutation_Sort(arr):
    while (is_sorted(arr) == False):
        shuffle(arr)
    return arr


def is_sorted(arr):
    n = len(arr)
    for i in range(0, n - 1):
        if (arr[i] > arr[i + 1]):
            return False
    return True


def shuffle(a):
    n = len(a)
    for i in range(0, n):
        r = random.randint(0, n - 1)
        a[i], a[r] = a[r], a[i]


def permutation(lst):
    # If lst is empty then there are no permutations

    if len(lst) == 0:
        return []

    # If there is only one element in lst then, only
    # one permutation is possible
    if len(lst) == 1:
        return [lst]

    l = []  # empty list that will store current permutation

    for i in range(len(lst)):
        m = lst[i]

        remLst = lst[:i] + lst[i + 1:]

        for p in permutation(remLst):
            l.append([m] + p)
    return l


if __name__ == "__main__":
    print((build_result_table().draw()))
    print((build_result_table1().draw()))
