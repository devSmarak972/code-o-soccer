#include "fira_comm.h"
#include "serial.h"
#include "cs.hpp"
#include "logger.h"
#include "skillSet.h"
#include <sys/time.h>
#include <unistd.h>
#include<bitset>
using namespace std;
using namespace Util;

namespace HAL
{

// #ifdef VISION_COMM
//   CS FIRAComm::cs_internal[5];
//   void FIRAComm::getSentData(int botid, int &vl, int &vr)
//   {
//     cs_internal[botid].enter();
// 	// NOTE: multiplying by 2 for new bot, which takes halved values
//     vl = command.data[botid*2]*2;
//     vr = command.data[botid*2+1]*2;
//     cs_internal[botid].leave();    
//   }
//   FIRAComm::FIRAComm()
//   {
//     std::cout<<"Inside firacomm"<<std::endl;
//     debug_cs = new CS();
//     // if (!sPort.Open("/dev/ttyUSB0", 38400))
//     // { 
//     //   Logger::abort("Could not open COMM port");
//     // }
//     for(int i = 0; i < 3; i++)
//     {
//       lastVR[i] = 0;
//       lastVL[i] = 0;
//     }
//     fp = fopen("trans.log", "w");
//     openLoop[0] = false;
//     openLoop[1] = false;
//     openLoop[2] = false;
//     // openLoop[3] = false;
//     // openLoop[4] = false;
//   }

//   FIRAComm::~FIRAComm()
//   {}
  
//   void FIRAComm::whenBotSendsData(int ourV_l, int ourV_r)
//   {
//     FILE *f = fopen("/home/robo/botplot/compare_dataset/response.txt", "a");
//     unsigned char botSendData = 0;
//     bool ok, really = true;
//     int botSendvL = sPort.ReadByteTimeout(4.0, ok);
//     really &= ok;
//     int botSendvR = sPort.ReadByteTimeout(4.0, ok);
//     really &= ok;
//     if(!really) {
//       sPort.Clear();
//     }
//     fprintf(f, "%d %d %d %d %d\n", really, ourV_l, ourV_r, botSendvL, botSendvR);
//     fclose(f);
//   }
  
//   void FIRAComm::writeCombinedPacket()
//   {
//       for(int i=0; i<5; i++) {
//         cs_internal[i].enter();
//       }
//       command.preamble = Strategy::HomeTeam::COLOR == Simulator::BLUE_TEAM ? (int8_t)126 : (int8_t)127;
// 	//  command.timestamp = 0;
//       sPort.Write(&command, sizeof(CombinedFIRAPacket));
      
// #ifdef BOTLOG
//       int reqBotId = 4;
//       whenBotSendsData(command.data[reqBotId*2], command.data[reqBotId*2+1]); //need to think of how to implement this now
// #endif
//       for(int i=4; i>=0; i--) {
//         cs_internal[i].leave();
//       }
//   }
  
//   void FIRAComm::sendCommand(int botID,
//                              float v_l,
//                              float v_r)
//   {
// 	printf("Bot Velocity(firacomm) %d: %d %d\n", botID, (int)v_l, (int)v_r);
// 	// NOTE: adding changes for new FIRA bot, which doubles the velocity value
// 	// so that the range is (-256, 255) instead of (-128, 127)
// 	v_l = v_l/2.;
// 	v_r = v_r/2.;    
//     cs_internal[botID].enter();		
//     command.data[botID*2] = (int8_t)v_l;
//     command.data[botID*2+1] = (int8_t)v_r;
//     cs_internal[botID].leave();
//   }
//   void FIRAComm::addCircle(int x, int y, unsigned int radius, unsigned int color = 0xFFFFFFFF)
//   {
//     Debug_Circle circle;
//     circle.set_x(x);
//     circle.set_y(y);
//     circle.set_radius(radius);
//     circle.set_color(color);
//     debug_cs->enter();
//     debug_circles.push_back(circle);
//     debug_cs->leave();
//   }
//   void FIRAComm::addLine(int x1, int y1, int x2, int y2, unsigned int color = 0xFFFFFFFF)
//   {
//     Debug_Line line;
//     line.set_x1(x1);
//     line.set_y1(y1);
//     line.set_x2(x2);
//     line.set_y2(y2);
//     line.set_color(color);
//     debug_cs->enter();
//     debug_lines.push_back(line);
//     debug_cs->leave();

//   }
//   int FIRAComm::xpos = 0;
//   int FIRAComm::ypos = 0;
//   float FIRAComm::angle = 0;
// #else

  CS FIRAComm::cs_internal[3];
  void FIRAComm::getSentData(int botid, int &vl, int &vr)
  {

  }

  FIRAComm::FIRAComm()
  {
    // std::cout<<"Inside firacomm 1"<<std::endl;
    debug_cs = new CS();

    // this->dgram_socket = socket(PF_INET, SOCK_DGRAM, 0);
    // this->dgram_socket_fira = socket(PF_INET, SOCK_DGRAM, 0);
    // this->dest.sin_family = AF_INET;
    // this->dest_fira.sin_family = AF_INET;
    // inet_aton("192.168.137.120", &this->dest.sin_addr); // 192.168.137.52
    // inet_aton("127.0.0.1",&this->dest_fira.sin_addr);
    // // inet_aton("192.168.137.167", &this->dest.sin_addr);

    // this->dest.sin_port = htons(4220); // 4220
    // this->dest_fira.sin_port = htons(20011); // 4210

    // this->dest.sin_port = htons(4210); 

    // BOT ID - 1

    int blue_team = 1;

      this->dgram_socket[0] = socket(PF_INET, SOCK_DGRAM, 0);
      this->dgram_socket[1] = socket(PF_INET, SOCK_DGRAM, 0);
      this->dgram_socket[2] = socket(PF_INET, SOCK_DGRAM, 0);

    
    for (int i = 0; i < 3; i++)
    {
      this->dest[i].sin_family = AF_INET;
    }

    if(blue_team)
    {
      inet_aton("10.42.0.40", &this->dest[0].sin_addr);
      this->dest[0].sin_port = htons(4210);
      inet_aton("10.42.0.238", &this->dest[1].sin_addr);
      this->dest[1].sin_port = htons(4220);
      inet_aton("10.42.0.189", &this->dest[2].sin_addr);
      this->dest[2].sin_port = htons(4230);
    }
    else
    {
      inet_aton("192.168.137.120", &this->dest[0].sin_addr);
      this->dest[0].sin_port = htons(4220);
      inet_aton("192.168.137.120", &this->dest[1].sin_addr);
      this->dest[1].sin_port = htons(4220);
      inet_aton("192.168.137.120", &this->dest[2].sin_addr);
      this->dest[2].sin_port = htons(4220);
    }



    
    

    for(int i = 0; i < 3; i++)
    {
      lastVR[i] = 0;
      lastVL[i] = 0;
    }

    fp = fopen("trans.log", "w");
    openLoop[0] = false;
    openLoop[1] = false;
    openLoop[2] = false;
    // openLoop[3] = false;
    // openLoop[4] = false;
  }

  FIRAComm::~FIRAComm()
  {}
  
  void FIRAComm::whenBotSendsData(int ourV_l, int ourV_r)
  {

  }

  void FIRAComm::writeCombinedPacket()
  {
      for(int i=0; i<3; i++) {
        cs_internal[i].enter();
      }



      
#ifdef BOTLOG
      int reqBotId = 4;
      whenBotSendsData(command.data[reqBotId*2], command.data[reqBotId*2+1]); //need to think of how to implement this now
#endif
      for(int i=4; i>=0; i--) {
        cs_internal[i].leave();
      }
  }

  void FIRAComm::sendCommand(int botID,
                             float v_l,
                             float v_r)
  {
    // v_l = v_l/2;
    // v_r = v_r/2;
    // int v_l1 = 50;
    // int v_r1 = -25;
    int v_l1 = v_l;
    int v_r1 = v_r;
    v_l = v_r1;
    v_r = v_l1;
    // #ifdef BOT_COMM
        cout<<"Bot Velocity(firacomm) "<<botID<<": "<<(int)v_l<<" "<<(int)v_r<<endl;
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
        sendto(this->dgram_socket[botID], asciiString.data(), asciiString.size(), 0, (struct sockaddr*)&this->dest[botID], sizeof(this->dest[botID]));


    // #else
    fira_message::sim_to_ref::Packet packet;
    char Sentence [1000];

    fira_message::sim_to_ref::Command* command = packet.mutable_cmd()->add_robot_commands();
    command->set_id(botID);
    command->set_yellowteam(Strategy::HomeTeam::COLOR == Simulator::BLUE_TEAM ? 0:1);
    command->set_wheel_left((int)v_l);
    command->set_wheel_right((int)v_r);
    std::string env;
    packet.SerializeToString(&env);
    

    sendto(this->dgram_socket_fira, env.data(), env.size(), 0, 
           (struct sockaddr*)&this->dest_fira, sizeof(this->dest_fira));
    // cs_internal[botID].leave();
    // #endif
  }

  void FIRAComm::addCircle(int x, int y, unsigned int radius, unsigned int color = 0xFFFFFFFF)
  {
    Debug_Circle circle;
    circle.set_x(x);
    circle.set_y(y);
    circle.set_radius(radius);
    circle.set_color(color);
    debug_cs->enter();
    debug_circles.push_back(circle);
    debug_cs->leave();
  }
  void FIRAComm::addLine(int x1, int y1, int x2, int y2, unsigned int color = 0xFFFFFFFF)
  {
    Debug_Line line;
    line.set_x1(x1);
    line.set_y1(y1);
    line.set_x2(x2);
    line.set_y2(y2);
    line.set_color(color);
    debug_cs->enter();
    debug_lines.push_back(line);
    debug_cs->leave();

  }
  int FIRAComm::xpos = 0;
  int FIRAComm::ypos = 0;
  float FIRAComm::angle = 0;

// #endif

}
