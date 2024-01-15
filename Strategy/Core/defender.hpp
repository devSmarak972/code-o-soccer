#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
    

using namespace std;
using namespace Strategy;
    
void defender(BeliefState* state, int botID)
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