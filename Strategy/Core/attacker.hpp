#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
#include "game.hpp"    

using namespace std;
using namespace Strategy;

// Naive example for attacker
void Simpler::attacker(BeliefState* state, int botId)
{
    print("Attacker\n");
    // attacker_skills->setbotID(botID);

    // if (Vec2D::dist(state->homePos[botID], state->ballPos) < BOT_RADIUS && state->ballPos.x > state->homePos[botID].x)
    // {
    //     if (state->homePos[botID].y < 0)
    //         Spin(botID, -500.0);
    //     if (state->homePos[botID].y > 0)
    //         Spin(botID, 500.0);
    // }
    // else
    {
        sexec->GoToPoint(botId, state, state->ballPos, 0, true, true);
    }
}