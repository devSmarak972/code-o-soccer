  // Naive Example for GoalKeeper
#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
    

using namespace std;
using namespace Strategy;

  void goalkeeper(BeliefState *state,int botID)
  {
    //print("GoalKeeper\n");

	Vec2D dpoint(OUR_GOAL_X+DBOX_HEIGHT,state->ballPos.y);

    if(dpoint.y > OUR_GOAL_MAXY)
      dpoint.y = OUR_GOAL_MAXY;
    if(dpoint.y < OUR_GOAL_MINY)
      dpoint.y = OUR_GOAL_MINY;
    GoToPoint(botID,state,dpoint,PI/2,false,false);
  }
