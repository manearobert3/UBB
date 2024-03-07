import socket
import threading
import struct
import random
import time
def udp_server_creation(ip_addr,port):
    udp_socket=socket.socket(family=socket.AF_INET,type=socket.SOCK_DGRAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_socket.bind((ip_addr,port))
    print("Server is starting udp broadcast")
    return udp_socket

def udp_client_creation():
    client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    print("You are CONNECTED")
    return client_socket

def tcp_client_creation(ip_address, port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((ip_address, port))
    print("You are CONNECTED")
    return client_socket

def tcp_send_int(sock, x):
    print("Sending: {data}".format(data=x))
    sock.send(struct.pack("!i", x))


def tcp_recv_int(sock):
    x = struct.unpack("!i", sock.recv(4))[0]
    print("Received: {data}".format(data=x))
    return x


def tcp_send_string(sock, string):
    print("Sending: {data}".format(data=string))
    sock.send(string.encode('ascii'))


def tcp_recv_string(sock, size=1024):
    string = sock.recv(size).decode('ascii')
    print("Received: {data}".format(data=string))
    return string

def udp_recv_string(sock):
    string, address = sock.recvfrom(1024)
    converted_string = string.decode('ascii')
    print("Received {data}".format(data=converted_string))
    return converted_string, address

def get_message(udp_socket):
    message, address = udp_recv_string(udp_socket)
    print(message)



def client_program():
    global finished
    host = socket.gethostname()
    port = 5555

    try:
        server_socket = tcp_client_creation(host, port)
        udp_socket = udp_client_creation()

    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)

    # t = threading.Thread(target=get_message, args=(udp_socket,))
    # t.start()
    finished=False
    while not finished:
        n=2

        try:
            for i in range(n):
                x = random.randint(0, 9)
                tcp_send_int(server_socket, i)
                tcp_send_int(server_socket, x)
            tcp_recv_int(server_socket)

        except socket.error as msg:
            print('Error: ', msg.strerror)
            server_socket.close()
            exit(-2)

        time.sleep(3)
    server_socket.close()


if __name__ == '__main__':
    client_program()