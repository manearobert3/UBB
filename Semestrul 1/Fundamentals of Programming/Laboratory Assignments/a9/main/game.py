import unittest

from texttable import Texttable
import random
# from main.exception import GameException
class GameException(Exception):
    def __init__(self, error):
        self.error = error

    def __str__(self):
        return repr(self.error)

class TestMatrix(unittest.TestCase):
    def setUp(self):
        self.test=Matrix(5,5)

    def test_spaces(self):
        result=self.test.matrix[4][4]
        self.assertEqual(result," ")

    def test_player_move(self):
        self.test.add_player_move(3, 3)
        result=self.test.matrix[3][3]
        self.assertEqual(result,"X")

    def test_verify(self):
        result=self.test.verify()
        self.assertEqual(result,True)




class Matrix:
    # method to create the matrix in which we will play the game
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.matrix=[]
        for i in range(self.rows+1):
            self.matrix.append([" "]* (self.cols+1))
        for i in range(self.rows+1):
            self.matrix[i][0] = i
        for j in range(self.cols+1):
            self.matrix[0][j] = j
        # #-space is taken
        # X-space is taken but by the player
        # O-space is taken by the computer

    # the computer strategy is simple and it checks for every valid move if the free spaces around it are the max
    # from all the spaces in the matrix
    def computer_strategy(self):
        cp_row = random.randint(0, self.rows)
        cp_col = random.randint(0, self.cols)
        while(self.matrix[cp_row][cp_col]!=" "):
            cp_row=random.randint(1,self.rows)
            cp_col=random.randint(1,self.cols)
        max=-1
        for row in range(0,self.rows):
            for col in range(0,self.cols):
                k=0
                if self.matrix[row][col] == " ":
                    k=k+1
                    if row - 1 >= 1 and self.matrix[row - 1][col] == " ":
                        print(self.matrix[row - 1][col])
                        k=k+1
                    if row + 1 <= self.rows and self.matrix[row + 1][col] == " ":
                        print(self.matrix[row + 1][col])
                        k=k+1
                    if row + 1 <= self.rows and col + 1 <= self.cols and self.matrix[row + 1][col + 1] == " ":
                        print(self.matrix[row + 1][col + 1])
                        k=k+1
                    if col + 1 <= self.cols and self.matrix[row][col + 1] == " ":
                        print(self.matrix[row][col + 1])
                        k=k+1
                    if col + 1 <= self.cols and row - 1 >= 1 and self.matrix[row - 1][col + 1] == " ":
                        print(self.matrix[row - 1][col + 1])
                        k=k+1
                    if col - 1 >= 1 and row - 1 >= 1 and self.matrix[row - 1][col - 1] == " ":
                        print(self.matrix[row - 1][col - 1])
                        k = k + 1
                    if col - 1 >= 1 and self.matrix[row][col - 1] == " ":
                        print(self.matrix[row][col - 1])
                        k=k+1
                    if col - 1 >= 1 and row + 1 <= self.rows and self.matrix[row + 1][col - 1] == " ":
                        print(self.matrix[row + 1][col - 1])
                        k = k + 1
                    if(k>=max and self.matrix[row][col] == " "):
                        cp_row=row
                        cp_col=col
                        max=k
        self.add_computer_move(cp_row,cp_col)
    #player move
    def add_player_move(self,row,col):
        if row<=0 or col<=0:
            raise GameException("Invalid move")
        if self.matrix[row][col]=="#" or self.matrix[row][col]=="O" or self.matrix[row][col]=="X":
            raise GameException("Invalid move")
        self.matrix[row][col]="X"
        if row-1>=1 and self.matrix[row-1][col]==" ":
            self.matrix[row-1][col]="#"
        if row+1<=self.rows and self.matrix[row+1][col]==" ":
            self.matrix[row+1][col]="#"
        if row+1<=self.rows and col+1<=self.cols and self.matrix[row + 1][col+1]==" ":
            self.matrix[row + 1][col+1] = "#"
        if col+1<=self.cols and self.matrix[row][col+1]==" ":
            self.matrix[row][col+1]="#"
        if col + 1 <= self.cols and row - 1 >= 1 and self.matrix[row - 1][col + 1] == " ":
            self.matrix[row - 1][col + 1] = "#"
        if col-1>=1 and row-1>=1 and self.matrix[row-1][col-1]==" ":
            self.matrix[row-1][col-1]="#"
        if col-1>=1 and self.matrix[row][col-1]==" ":
            self.matrix[row][col - 1] = "#"
        if col - 1 >= 1 and row+1<=self.rows and self.matrix[row+1][col - 1] == " ":
            self.matrix[row+1][col - 1] = "#"
    def add_computer_move(self,row,col):
        if row<=0 or col<=0:
            raise GameException("Invalid move")
        if self.matrix[row][col]=="#" or self.matrix[row][col]=="O" or self.matrix[row][col]=="X":
            raise GameException("Invalid move")

        self.matrix[row][col]="O"
        if row-1>=1 and self.matrix[row-1][col]==" ":
            self.matrix[row-1][col]="#"
        if row+1<=self.rows and self.matrix[row+1][col]==" ":
            self.matrix[row+1][col]="#"
        if row+1<=self.rows and col+1<=self.cols and self.matrix[row + 1][col+1]==" ":
            self.matrix[row + 1][col+1] = "#"
        if col+1<=self.cols and self.matrix[row][col+1]==" ":
            self.matrix[row][col+1]="#"
        if col+1<=self.cols and row-1>=1 and self.matrix[row-1][col+1]==" ":
            self.matrix[row-1][col+1]="#"
        if col-1>=1 and row-1>=1 and self.matrix[row-1][col-1]==" ":
            self.matrix[row-1][col-1]="#"
        if col-1>=1 and self.matrix[row][col-1]==" ":
            self.matrix[row][col - 1] = "#"
        if col - 1 >= 1 and row+1<=self.rows and self.matrix[row+1][col - 1] == " ":
            self.matrix[row+1][col - 1] = "#"

    def verify(self):
        for i in range(0,self.rows+1):
            for j in range(0,self.cols+1):
                if self.matrix[i][j]==" ":
                    return True
        return False

    def print_matrix(self):
        table = Texttable()
        for row in self.matrix:
            table.add_row(row)
        print(table.draw())
class Console:
    def __init__(self,game):
        self.game=game

    def menu(self):
        self.game.print_matrix()
        while True:
            try:
                x = int(input("Input Height"))
                y = int(input("Input Width"))
                self.game.add_player_move(x, y)
                if self.game.verify() == False:
                    print("Player wins!")
                    return False
                self.game.computer_strategy()
                if self.game.verify() == False:
                    print("Computer wins!")
                    return False
                self.game.print_matrix()

            except Exception as e:
                print(e)

while True:
    try:
        lines = int(input("Please enter a number: "))
        columns=int(input("Please enter a number: "))
        break
    except ValueError:
        print("Please input an integer")

game=Matrix(lines,columns)
console= Console(game)
console.menu()
unittest.main()
