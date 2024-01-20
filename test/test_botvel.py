import socket
import argparse


def encode_msg(v_l,v_r):

    max_vel = (1 << 10) - 1
    left_vel = min(abs(int(v_l)), max_vel)
    right_vel = min(abs(int(v_r)), max_vel)

    left_bits = format(left_vel, '010b')
    right_bits = format(right_vel, '010b')

    # print("LEFT BITS ",left_bits)

    bit_string = (f"1{right_bits}00000" if v_r < 0 else f"0{right_bits}00000") + (f"1{left_bits}00000" if v_l < 0 else f"0{left_bits}00000")
    # print("Bit string: ", bit_string)
    ascii_string = ""
    for i in range(0, len(bit_string), 8):
        chunk = bit_string[i:i + 8]
        # print("Chunk: ", chunk)
        ascii_string += chr(int(chunk, 2))
        # print("Ascii string: ", ascii_string)

    # print(f"BIT String: {bit_string}")

    return ascii_string

def test_botvel(port,ip,v_l,v_r):
    # Create a socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Send this encoded message to the robot
    i = 0

    while i<1000:
        s.sendto(encode_msg(v_l,v_r).encode('utf-8'), (ip, port))
        i+=1
        # print("Sent message")

    s.close()

if __name__ == "__main__":
    # Pass the port and ip address of the robot as arguments and take from command line

    parser = argparse.ArgumentParser()

    parser.add_argument("--port", help="Port number of the robot", type=int, default=5005)
    parser.add_argument("--ip", help="IP address of the robot", type=str, default="10.42.0.40")
    parser.add_argument("--v_l", help="Left wheel velocity", type=int, default=20)
    parser.add_argument("--v_r", help="Right wheel velocity", type=int, default=30)
    args = parser.parse_args()

    port = args.port
    ip = args.ip
    v_l = args.v_l
    v_r = args.v_r

    print("VL ",v_l)
    print("VR ",v_r)


    test_botvel(port,ip,v_l,v_r)
    
    

    