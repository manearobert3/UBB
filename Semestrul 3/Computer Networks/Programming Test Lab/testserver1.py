import socket
import struct
import threading
import time

import random

def tcp_send_int(sock, x):
    print("Sending: {data}".format(data=x))
    sock.send(struct.pack("!i", x))


def udp_server_creation(ip_addr,port):
    udp_socket=socket.socket(family=socket.AF_INET,type=socket.SOCK_DGRAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    #udp_socket.bind((ip_addr,port))
    print("Server is starting udp broadcast")
    return udp_socket

def udp_client_init():
    client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    print("You are CONNECTED")
    return client_socket

def tcp_server_creation(ip_addr,port):
    tcp_socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    tcp_socket.bind((ip_addr,port))
    tcp_socket.listen(5)
    print("tcp connection created")
    return tcp_socket

def tcp_recv_int(sock):
    x = struct.unpack("!i", sock.recv(4))[0]
    print("Received: {data}".format(data=x))
    return x

def worker(peer_socket):
    print('CONNECTED Client', peer_socket.getpeername())
    try:
        nr_q = tcp_recv_int(peer_socket)
        for i in range(nr_q):
            value = tcp_recv_int(peer_socket)
            string = i +":"+value;
            print("{i} : {value}".format(i=i,value=value))

        x = random.randint(1, 10)
        tcp_send_int(peer_socket, x)
    except socket.error as msg:
        print('Error:', msg.strerror)

    time.sleep(12)
    try:
        x = random.randint(1, 10)
        tcp_send_int(peer_socket, x)
    except socket.error as msg:
        print('Error:', msg.strerror)
    peer_socket.close()
    print("Game ended")



def udp_send_string(sock, string, dest_address):
    print("Sending {data}".format(data=string))
    sock.sendto(string.encode('ascii'), ('255.255.255.255',5555))

def udp_worker(sockets, udp_socket):
    number_times=6
    while True:

        for i in range (6):
            # for adress in sockets:
            #     string="asdasds"
            udp_send_string(udp_socket,"asdasd",5555)
            time.sleep(2)
        break

def start_server():
    global sockets,threads,client_count,threads,sockets
    ip='0.0.0.0'
    port=5555
    portUdp=5556
    try:
        udp_socket=udp_server_creation(ip,portUdp)
        tcp_socket=tcp_server_creation(ip,port)
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    while True:
        (peer_socket, peer_address) = tcp_socket.accept()
        sockets.append(peer_address)
        # t = threading.Thread(target=worker, args=(peer_socket,))
        # threads.append(t)
        # t.start()

        t1 = threading.Thread(target=udp_worker, args=(sockets, udp_socket))
        threads.append(t1)
        t1.start()

if __name__=='__main__':
    sockets=[]
    threads=[]
    start_server()
