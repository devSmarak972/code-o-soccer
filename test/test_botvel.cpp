#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include<bits/stdc++.h>
#include<time.h>
#include<thread>
#include <chrono>
using namespace std;



int main(int argc,char *argv[]){

    int dgram_socket = socket(PF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;

    char* ip = argv[1];
    int port = atoi(argv[2]);

    inet_aton(ip, &dest.sin_addr);
    dest.sin_port = htons(port);

    int v_r = atoi(argv[3]);
    int v_l = atoi(argv[4]);

    cout<<"Bot Velocity(firacomm) "<<": "<<(int)v_l<<" "<<(int)v_r<<endl;
    const int max_vel = (1<<10) - 1;
    int leftvel = std::min(abs((int)v_l),max_vel);
    int rightvel = std::min(abs((int)v_r),max_vel);
    std::bitset<10> leftBits(leftvel);
    std::bitset<10> rightBits(rightvel);
    std::string bitString =  (v_l < 0 ? "1" : "0") + leftBits.to_string() + "00000" + (v_r < 0 ? "1" : "0") +  rightBits.to_string() + "00000";
    std::string asciiString;
    for (size_t i = 0; i < bitString.length(); i += 8) {
        std::bitset<8> chunk(bitString.substr(i, 8));
        asciiString += static_cast<char>(chunk.to_ulong());
    }
    std::cout << "Ascii String: " << bitString <<endl;

    while (true)
    {
        sendto(dgram_socket, asciiString.data(), asciiString.size(), 0, (struct sockaddr*)&dest, sizeof(dest));
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        // sleep(2);
    }
    

}