from FiniteAutomata import FiniteAutomata
from Parser import Parser

def test_check_word():
    fa = FiniteAutomata()

    assert fa.check_word("a") == True, "Test case 1 failed"
    assert fa.check_word("abc") == True, "Test case 2 failed"
    assert fa.check_word("123") == True, "Test case 3 failed"
    assert fa.check_word("a1b2c3") == True, "Test case 4 failed"

    assert fa.check_word("1a") == False, "Test case 5 failed"
    assert fa.check_word("a!") == False, "Test case 6 failed"
    assert fa.check_word("abc123!") == False, "Test case 7 failed"
    assert fa.check_word(" ") == False, "Test case 8 failed"
    #assert fa.check_word("\"aAAA\"") == True, "Test case 9 failed"

    print("All test cases passed!")



if __name__ == '__main__':

    test_check_word()
    parser = Parser()
    parser.parse_file("p3.txt")
    fa = FiniteAutomata()
    fa.menu()
