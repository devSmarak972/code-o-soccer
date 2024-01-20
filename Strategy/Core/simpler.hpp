#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
#include "skills.hpp"
#include <fstream>
#include "game.h"

using namespace Strategy;


void Simpler::run()
  {
	
    Util::CS loggerCS;
    Util::Logger logger("timelog.log", Util::Logger::Write, loggerCS);
    Kalman      kFilter ;
    VisionThread vThread(&kFilter);
    vThread.start();
    // PExec pExec(&state);
  	unsigned char   refBoxCmdCounter = -1;
  	HAL::RefBoxCmd  refBoxCmdSh;//  = new RefBoxCmd();
  	#ifdef RUN_REFBOX
    Util::CS        refBoxCS;//     = new CS();
    RefBoxThread    refBoxThread = RefBoxThread::getInstance(&refBoxCmdSh, &refBoxCS);
    refBoxThread.start();
	#endif

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
    //   writer_mutex->enter();

		cout<<ustate.update()<< ": state update"<<endl;
		// BeliefState& state1 = *state;

		kFilter.update(ustate);

    //   writer_mutex->leave();


#ifdef RUN_REFBOX
      {
        // Critical Section protected by refBoxCS
        refBoxCS.enter();
        // Updating from Referee Box and the Game State
      //  printf("refBoxCmdSh.cmdCounter = %d\n",refBoxCmdSh.cmdCounter);
        if (refBoxCmdCounter != refBoxCmdSh.cmdCounter)
        {
          printf("GOT COMMAND FROM REFEREE!!!!\n");
          ustate.refreeUpdated = true;
          Util::Logger::toStdOut("Ref Box Updated to %d\n", refBoxCmdSh.cmdCounter);
          refBoxCmdCounter      = refBoxCmdSh.cmdCounter;
          ustate.updateStateFromRefree(refBoxCmdSh);
        }
		printf("%d\t%d\n",refBoxCmdSh.goalsBlue,refBoxCmdSh.goalsYellow);
        refBoxCS.leave();
      } // End of Critical Section protected by refBoxCS
#endif // RUN_REFBOX

	  
		int vl=0, vr=0;
		// SkillSet::comm->getSentData(0, vl, vr);
		printf( "sent velocity = (%d, %d), vision velocity = (%f, %f), vision pos = (%d, %d)\n", vl, vr, 
		kFilter.homeVlVr[0].x, kFilter.homeVlVr[0].y, ustate.homePos[0].x, ustate.homePos[0].y);
        // SkillSet::comm->writeCombinedPacket();
   //**************************************** END OF TESTING ************************************************  

         usleep(16000);  // Adding sleep to this thread of execution to prevent CPU hogging
		 cout<<"Before sending ustate halted "<<ustate.pr_gameRunning<<endl;
    //   GoToBall(1,true);
	  	game(&ustate);
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
		cout<<"Inside game"<<endl;

		if(state->pr_gameRunning){

			cout<<"Inside not haulted"<<endl;
     

          attacker(state,1);
          // defender(state,1);
          // goalkeeper(state,1);
          // GoToBall(2,true);
      


		} 
		else{
			std::cout<<"Inside haulted"<<std::endl;
			refComm->sendCommand(1,0,0);
			refComm->sendCommand(0,0,0);
			refComm->sendCommand(2,0,0);
		}


		// if (state->ourBotNearestToBall == 2 || state->ballPos.x > 0) {
		// 	attacker(state, 2);
		// 	// defender(state, 1);
		// }
		// else {
		// 	attacker(state, 1);
		// 	// defender(state, 2);
		// }
		// // goalkeeper(state, 0);
	}