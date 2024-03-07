__author__ = 'dadi'

import socket
import threading
import random
import struct
import sys
import time

random.seed()
start=1; stop=2**17-1
my_num= random.randint(start,stop)
print('Server number: ',my_num)
mylock = threading.Lock()
client_guessed=False
winner_thread=0
e = threading.Event()
e.clear()
threads = []
client_count=0
numere={}
def worker(cs):
    global mylock, client_guessed, my_num, winner_thread, client_count,e

    my_idcount=client_count
    #print('client #',client_count,'from: ',cs.getpeername(), cs )
    #message='Hello client #'+str(client_count)+' ! You are entering the number guess competion now !'
    #cs.sendto(bytes(message,'ascii'))
    #while not client_guessed:
    if True:
            cnumber=cs.recvfrom(1)
            cnumber=struct.unpack('!I',cnumber)[0]
            numere[addrc] =cnumber;
            if cnumber > my_num:
                cs.sendto(b'S',addrc)
            if cnumber < my_num:
                cs.sendto(b'H',addrc)
            if cnumber== my_num:
                client_guessed=True


    if client_guessed:
        for key,value in numere.items():
            if(value==my_num):
                cs.sendto(b'G',addrc)
                print('We have a winner', cs.getpeername())
        else:
            cs.sendto(b'L',addrc)
    time.sleep(1)
    cs.close()
    print("Worker Thread ",my_idcount, " end")


def resetSrv():
    global mylock, client_guessed, winner_thread, my_num, threads,e, client_count
    client_guessed = False
    winner_thread=-1
    client_count = 0
    my_num = random.randint(start,stop)
    print('Server number: ',my_num)


if __name__=='__main__':
    try:
        rs=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        rs.bind( ('0.0.0.0',1234) )
      #  rs.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)

    while True:
        client_socket,addrc = rs.recvfrom(4)
        worker(rs,)
