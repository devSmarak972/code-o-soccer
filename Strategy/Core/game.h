#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
#include "skills.hpp"
#include <fstream>
// #include "attacker.hpp"
#include "fira_comm.h"
using namespace HAL;
#include "beliefState.h"
using namespace std;


class Simpler : public Util::Thread,public Executor
{
  public:


  void attacker(BeliefState* state,int botID)
  {
    // attacker_skills->setbotID(botID);
    
    if (Vec2D::dist(state->homePos[botID], state->ballPos) < BOT_RADIUS*1.1 )
    {

        if (state->homePos[botID].y < 0)
            Spin(botID, -150.0);
        if (state->homePos[botID].y > 0)
            Spin(botID, 150.0);
    }
    else
    {
      printf("go to point %d",state->homePos[1].x);
      GoToBall(botID,true);
        // GoToPoint(botID, state, state->ballPos, 0, true, true);
    }

  };
  void defender(BeliefState* state,int botID)
  {
   //print("Defender\n");
		//It follows the ball
		Vec2D dpoint;
		dpoint.x = -HALF_FIELD_MAXX / 4;
		if (state->ballPos.x < 0) {
			dpoint.x = (OUR_GOAL_X + DBOX_HEIGHT + state->ballPos.x) / 2;
		}
		dpoint.y = state->ballPos.y;
		GoToPoint(botID, state, dpoint, PI / 2, false, false); 
  }
  void goalkeeper(BeliefState* state,int botID){
    Vec2D dpoint(OUR_GOAL_X+DBOX_HEIGHT,state->ballPos.y);

    if(dpoint.y > OUR_GOAL_MAXY)
      dpoint.y = OUR_GOAL_MAXY;
    if(dpoint.y < OUR_GOAL_MINY)
      dpoint.y = OUR_GOAL_MINY;
    GoToPoint(botID,state,dpoint,PI/2,false,false);
  }
public:
  bool &running;
  BeliefState &ustate;
  // Simulator::TeamColor color;
	// SkillSet* attacker_skills,defender_skills,goalkeeper_skills;
  // Executor* sexec;
  Simpler(bool &running_, BeliefState &state_):
  running(running_),ustate(state_),Executor(&state_) {
  }
  void game(BeliefState* state);
  void run();
};