# Solve the problem from the first set here
def NrPrim(n):
    """
    Problem number 1.
    The function takes a number n
    Then starts searching for the next prime number
    Bigger than number n and returns it.
    :param n:
    :return n:
    """
    if n < 2 :
        return 2
    a = True
    while a == True:
        n = n + 1
        a = False
        a=verification_prime(n)

    return n
def verification_prime(n):
    for i in range(2, int (n/2),1):
        if n%i == 0:
            return True
    return False


n = int(input('Input n='))
print(NrPrim(n))