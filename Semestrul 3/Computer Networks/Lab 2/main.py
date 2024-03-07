__author__ = 'dadi'

import socket, struct, random, sys, time

if __name__ == '__main__':
    try:
        s = socket.create_connection(('localhost', 1234))
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    finished = False
    sr = 1.0

    er = 2 ** 17 - 1.0
    er=float(er)

    random.seed()
    data = s.recv(1024)
    print(data.decode('ascii'))
    step_count = 0
    while not finished:
        my_num= round(random.uniform(sr, er),3)
        try:
            s.sendall(struct.pack('!f', my_num))
            answer = s.recv(1)
        except socket.error as msg:
            print('Error: ', msg.strerror)
            s.close()
            exit(-2)
        step_count += 1
        print('Sent ', my_num, ' Answer ', answer.decode('ascii'))
        if answer == b'H':
            sr = my_num
        if answer == b'S':
            er = my_num
        if answer == b'G' or answer == b'L':
            finished = True
        time.sleep(0.25)

    s.close()
    if answer == b'G':
        print("I am the winner with", my_num, "in", step_count, "steps")
    else:
        print("I lost !!!")
#    input("Press Enter")



