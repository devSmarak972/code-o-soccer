import socket

#  Receive data from the udp socket


def receive_data(port, ip):
    # Create a socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Bind to the port
    s.bind((ip, port))

    # Receive data
    while True:
        data, addr = s.recvfrom(1024)
        ascii_string = data.decode('utf-8')
        bit_string = ''.join(format(ord(char), '08b') for char in ascii_string)
        print(f"Received Bit String: {bit_string}")



if __name__ == "__main__":
    port = 5005
    ip = "127.0.0.1"

    receive_data(port, ip)