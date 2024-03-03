# Solve the problem from the second set here
def palindrom(n):
    """
    Problem number 10.
    The function takes an integer n
    And it returns the number
    With a reversed order of its digits in variable a
    :param n:
    :return a:
    """
    a = 0
    while n != 0:
        a = a * 10 + n % 10
        n = n // 10
    return a

n = int(input('Input n'))
print(palindrom(n))