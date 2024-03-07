__author__ = 'dadi'
import socket, struct, random,sys, time


if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    finished=False
    sr = 1; er=2**17-1
    random.seed()

   # data,addr=s.recvfrom(1024)
    #print(data.decode('ascii'))
    step_count=0
    while not finished:
        my_num=random.randint(sr,er)
        try:
           # s.sendall( struct.pack('!I',my_num) )
            s.sendto(struct.pack('!i', my_num),('localhost',1234))
            answer=s.recvfrom(1)
        except socket.error as msg:
            print('Error: ',msg.strerror)
            s.close()
            exit(-2)
        step_count+=1
        print('Sent ',my_num,' Answer ',answer.decode('ascii'))
        if answer==b'H':
            sr = my_num
        if answer==b'S':
            er = my_num
        if answer==b'G' or answer==b'L':
            finished=True
        time.sleep(0.25)

    s.close()
    if answer==b'G':
        print("I am the winner with",my_num,"in", step_count,"steps")
    else:
        print("I lost !!!")
#    input("Press Enter")