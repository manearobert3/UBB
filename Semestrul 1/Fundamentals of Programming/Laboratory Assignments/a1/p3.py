# Solve the problem from the third set here
def PerfectNumber(n):
    """
    Problem number 15
    This function goes through all the numbers
    smaller than a given natural number n
    and verifies if it is a perfect number
    :param n:
    :return i:
    """
    if n < 1:
        print('There are no perfect numbers smaller than given n')
    for i in range(n-1, 5, -1):
        if sum_of_divisors(i) == i:
            return i
    print('There are no perfect numbers smaller than given n')

def sum_of_divisors(n):
    s=0
    for k in range(1, n-1):
        if n % k == 0:
            s = s + k
    return s


n = int(input('Input n='))
print(PerfectNumber(n))