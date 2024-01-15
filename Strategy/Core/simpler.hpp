#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
#include "skills.hpp"
#include <fstream>
#include "game.h"

using namespace std;
using namespace Strategy;

void Simpler::run()
  {
	
    Util::CS loggerCS;
    Util::Logger logger("timelog.log", Util::Logger::Write, loggerCS);
    Kalman      kFilter ;
    VisionThread vThread(&kFilter);
    vThread.start();
    // PExec pExec(&state);


    bool isRunning = true; 
    //    Util::Timer timer;
	int loopcount = 0;
	unsigned long long int t1=0,t2=0;
	usleep(1000);
			
//	ofstream myfile;
//	myfile.open ("ballPosLog.txt");
	// FILE *f1 = fopen("./tmp/bot_vel_data.txt", "w");
	int aid=4;int rid=4;
	int PtimeID=0;
    while(running)
    {

    //      timer.start();

        kFilter.update(state);
		state.update();

	  
		int vl=0, vr=0;
		// SkillSet::comm->getSentData(0, vl, vr);
		printf( "sent velocity = (%d, %d), vision velocity = (%f, %f), vision pos = (%f, %f)\n", vl, vr, 
		kFilter.homeVlVr[0].x, kFilter.homeVlVr[0].y, kFilter.homePose[0].x, kFilter.homePose[0].y);
        // SkillSet::comm->writeCombinedPacket();
   //**************************************** END OF TESTING ************************************************  

         usleep(16000);  // Adding sleep to this thread of execution to prevent CPU hogging
      game(&state);
		// attacker_skills->goToBall(params);

    }
	// fclose(f1);
    vThread.stop();
    Util::Logger::toStdOut("Exiting process");
//	myfile.close();
    return;
  }

void Simpler::game(BeliefState* state)
	{
		if (state->ourBotNearestToBall == 2 || state->ballPos.x > 0) {
			attacker(state, 2);
			defender(state, 1);
		}
		else {
			attacker(state, 1);
			defender(state, 2);
		}
		goalkeeper(state, 0);
	}