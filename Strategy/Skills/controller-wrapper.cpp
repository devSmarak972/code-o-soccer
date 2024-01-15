#include "controller-wrapper.hpp"
#include <iostream>
#include "ballinterception.cpp"
using namespace std;

MiscData ControllerWrapper::genControls_(Pose s, Pose e, int &vl, int &vr, double finalVel) {
    assert(ctrlType == POINTCTRL);
    Pose x = s;
    for(deque<pair<int,int> >::iterator it = uq.begin(); it != uq.end(); it++) {
        x.updateNoDelay(it->first, it->second, timeLC);
    }
//    int prevSpeed = max(fabs(prevVl), fabs(prevVr));
    double prevSpeed = (prevVl+prevVr)/2;
    double prevOmega = (prevVr- prevVr)/(d);
    MiscData m = (*fun)(x, e, vl, vr, prevSpeed,prevOmega, finalVel);
    prevVl = vl; prevVr = vr;
    uq.push_back(make_pair<int,int>((int)vl, (int)vr));
    uq.pop_front();
    return m;
}

MiscData ControllerWrapper::genControls_(Pose s, int &vl, int &vr, double time, bool useTime) {
    assert(ctrlType == TRACKCTRL);
    Pose x = s;
    for(deque<pair<int,int> >::iterator it = uq.begin(); it != uq.end(); it++) {
        x.updateNoDelay(it->first, it->second, timeLC);
    }
    if (isFirstCall) {
        isFirstCall = false;
        gettimeofday(&startTime, NULL);
    }
    double elapsedS;
    printf("elapsed\n");
    if (!useTime) {
        struct timeval nowTime;
        gettimeofday(&nowTime, NULL);
        elapsedS = (nowTime.tv_sec-startTime.tv_sec)+(nowTime.tv_usec-startTime.tv_usec)/1000000.0;        
    } else {
        elapsedS = time;
    }
    // should offset elapsedS by the number of packet delay!!!
    elapsedS += k*timeLCMs/1000.;
    MiscData m = tracker.genControls(x, vl, vr, prevVl, prevVr, elapsedS);
    prevVl = vl; prevVr = vr;
    uq.push_back(make_pair<int,int>((int)vl, (int)vr));
    uq.pop_front();
    return m;
}

Pose ControllerWrapper::getReferencePose() {
	// does not work with motion-simulation simulator
	double t = getCurrentTimeS();
	Pose ref(tracker.getTraj()->x(t)*fieldXConvert, tracker.getTraj()->y(t)*fieldXConvert, tracker.getTraj()->theta(t));
	return ref;
}

int ControllerWrapper::ballPredictionCheck(Vector2D<float> botPos, Vector2D<float> ballPos, Vector2D<float> ballVel, float deviatedDist, double splineTotalTime){
	// to check if the spline end point is not very far from ball predictedpoint
	double t = getCurrentTimeS();
	Vector2D<float> ballPredictedPose = BallInterception::predictBallPose(botPos, ballPos, ballVel, splineTotalTime-t, Vector2D<float>(0,0));
	Vector2D<float> botPose(tracker.getTraj()->x(splineTotalTime)*fieldXConvert, tracker.getTraj()->y(splineTotalTime)*fieldXConvert);
	if (Vector2D<float>::dist(ballPredictedPose, botPose) > deviatedDist)
		return 1;
	return 0;
}
ControllerWrapper::ControllerWrapper(FType fun, int start_vl, int start_vr, int k):fun(fun), k(k), ctrlType(POINTCTRL), tracker(),
                                                                startTime(), isFirstCall(true){
    for(int i = 0; i < k; i++)
        uq.push_back(make_pair<int,int>((int)start_vl,(int)start_vr));
    prevVl = prevVr = 0;
}
ControllerWrapper::ControllerWrapper(Trajectory *traj, int start_vl, int start_vr,  int k):k(k), ctrlType(TRACKCTRL), tracker(traj),
                                                                       startTime(), isFirstCall(true){
    for(int i = 0; i < k; i++)
        uq.push_back(make_pair<int,int>((int)start_vl,(int)start_vr));
    prevVl = prevVr = 0;
}

ControllerWrapper::ControllerWrapper(Trajectory *traj, int start_vl, int start_vr,  int k, int prevVL, int prevVR):k(k),
	ctrlType(TRACKCTRL), tracker(traj), startTime(), isFirstCall(true), prevVl(prevVL), prevVr(prevVR){
    for(int i = 0; i < k; i++)
        uq.push_back(make_pair<int,int>((int)start_vl,(int)start_vr));
}

void ControllerWrapper::reset() {
    isFirstCall = true;
}
void ControllerWrapper::setTraj(Trajectory* traj) {
    tracker.setTraj(traj);
    reset();
}
Pose ControllerWrapper::getPredictedPose(Pose s) {
    Pose x = s;
    for(deque<pair<int,int> >::iterator it = uq.begin(); it != uq.end(); it++) {
        x.updateNoDelay(it->first, it->second, timeLC);
    }
    return x;
}

double ControllerWrapper::getCurrentTimeS() const
{
    if (isFirstCall)
        return 0;
    struct timeval nowTime;
    gettimeofday(&nowTime, NULL);
    double elapsedS = (nowTime.tv_sec-startTime.tv_sec)+(nowTime.tv_usec-startTime.tv_usec)/1000000.0;
    return elapsedS;
}
MiscData ControllerWrapper::genControls(Pose s, Pose e, int &vl, int &vr, double finalVel) {	
    cout << "controlelrwrapper " <<endl;

    if (ctrlType == POINTCTRL) {
            cout << "controlelrwrapper 1 " << endl;

        return genControls_(s, e, vl, vr, finalVel);
    } else {
                    cout << "controlelrwrapper 2" << endl;

        return genControls_(s, vl, vr);
    }
}

MiscData ControllerWrapper::genControlsTrajSim(Pose s, int &vl, int &vr, double t)
{
    assert (ctrlType == TRACKCTRL);
    return genControls_(s, vl, vr, t, true);
}

Vector2D<float> ControllerWrapper::getDelayedVel()
{
    return Vector2D<float>(uq.back().first, uq.back().second);
}

Vector2D<int> ControllerWrapper::getPrevDelVel()
{
    return Vector2D<int>(uq[uq.size()-2].first, uq[uq.size()-2].second);
}

Pose ControllerWrapper::getNewStartPose(){
    double elapsedS;
    struct timeval nowTime;
    gettimeofday(&nowTime, NULL);
    elapsedS = (nowTime.tv_sec-startTime.tv_sec)+(nowTime.tv_usec-startTime.tv_usec)/1000000.0;
//	if(elapsedS < 0.075)
//		return s;
    return tracker.getNewStartPose(elapsedS);
}
