//	Warning! Do not modify this file

/*	It is through the skill layer that the MyStrategy layer talks to the Simulator/Actual robots
	1)namespace MyStrategy implements 2 important classes (LocalAvoidance and BeliefState) along
	with several other important functions namely: GoToPoint, GoToBall, TurnToAngle, Spin etc.
	2)Important functions are explained in brief below
	-> GoToPoint uses obstacle avoidance to reach a destination point while GoToPointStraight
	uses direct path to reach destination without any obstacle avoidance
	-> void maingotopoint(int botID,BeliefState *state, Vector2D<int> dpoint, float finalvel, 
	float finalslope, float clearance = CLEARANCE_PATH_PLANNER,bool increaseSpeed=0,bool 
	avoid_obstacle = true);
	It implememts gotopoint with greater flexibility of customizing path.
	Also clearance, increaseSpeed and avoid_obstacle are optional arguments with default values 
	set to CLEARANCE_PATH_PLANNER, 0 , 1 respectively
	3)bool pointyInField(Vector2D<int> final)
*/
#pragma once
#ifndef SKILLSW_H
#define SKILLSW_H


#include <cassert>
#include <string>
#include <vector>

#include "Utils/comdef.h"
#include "Utils/pathPlanners.h"
#include "Core/beliefState.h"
#include "config.h"
#include "HAL/comm.h"
#include "geometry.hpp"
#include "skillSet.h"
#include "mainheaders.hpp"
#include "thread.h"
#include "strategygui_thread.hpp"
#include "command-packet.pb.h"
#include "tExec.h"

#include <fstream>
using namespace std;
using namespace Strategy;

template <class T> class Vector2D;
typedef Vector2D<int> Vec2D;
// Use Vec2D to define a point with x and y as coordinate

   class Executor: public SkillSet
  {
    /****************************************************List of Skills******************************************************/
    // Go to a point with obstacle avoidance.
    public:
    Executor(const BeliefState* state, int botID) : SkillSet(state, botID){

        
    };

    void GoToPoint(int botID,BeliefState *state,Vector2D<int> dpoint, float finalslope, bool increaseSpeed, bool shouldAlign)
    {
          setbotID(botID);
         Strategy::SParam param;
        param.GoToPointP.x=dpoint.x;
        param.GoToPointP.y=dpoint.y;
        param.GoToPointP.finalslope=finalslope;
        param.GoToPointP.align=shouldAlign;
        param.GoToPointP.finalVelocity=0;
        param.GoToPointP.increaseSpeed=increaseSpeed;

        // bool align;
        // float finalVelocity;
        goToPoint(param); 
    };
    
    // Go to point without obstacle avoidance.
    void GoToPointStraight(int botID,BeliefState *state,Vector2D<int>dpoint,float finalslope, bool increaseSpeed, bool shouldAlign);
    
    // Go to ball: If shouldAlign is true, then bot will align with the line joining the ball and the goal else will go straightaway.
    void GoToBall(int botID,bool shouldAlign)
    {
        printf(" %d,%d",state->homePos[1].x,state->homePos[1].y);
        setbotID(botID);
         Strategy::SParam param;
        param.GoToBallP.align=shouldAlign;
        goToBall(param);

    }
    // Angle in radian
    void TurnToAngle(int botID,BeliefState *state,float angle);
    
    // Control the bot directly.
    void Velocity(int botID,int vl,int vr);

    // Spin the bot. Positive angular speed for clockwise rotation
    void Spin(int botID,float angularSpeed)
    {
     setbotID(botID);
         Strategy::SParam param;
        param.SpinP.radPerSec=angularSpeed;
        spin(param); 
    };// spped in radians
    
    // Stop the bot.
    void Stop(int botID);
	
	void vibrate(BeliefState *state,int botID,int c);
    /*
     * For those who want to know more may checkout the function definiton in skills.cpp
     * And you can also add new skills depending upon your need here.
    */
    /*********************************************************************************************************************/
    

    bool pointyInField(Vector2D<int> final);

    void maingotopoint(int botID,BeliefState *state, Vector2D<int> dpoint, float finalvel, float finalslope, float clearance = CLEARANCE_PATH_PLANNER,bool increaseSpeed=0,bool avoid_obstacle = true);
    // static void clearDebugData()
    // {
    //   #ifdef FIRASSL_COMM
    //     comm->clearDebugData();
    //   #endif
    // }
  };



#endif // SKILLSW_H
