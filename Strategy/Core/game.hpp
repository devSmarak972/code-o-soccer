#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"
#include "attacker.hpp"
#include "defender.hpp"
#include "goalkeeper.hpp"
#include <fstream>

using namespace std;
using namespace Strategy;


// Write your strategy here in game function.
	// You can also make new functions and call them from game function.
	void game(BeliefState* state)
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