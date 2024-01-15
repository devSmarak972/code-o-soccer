#include "velocity-profile.hpp"
#include <limits>
#include "arclength-param.hpp"
#include <iostream>

using namespace std;
namespace VelocityProfiling {
// isolated constraints

// k: curvature ( = w/v), 1/cm
// vsat: max vl (or vr) in  cm/s
// vwmax: max centripetal acceleration, cm/s^2
// return: vmax, cm/s
double vmax_isolated(double k, double vsatu, double vwmaxi ) {
  double res;
  // saturation considering curvature
  // remember, v is always positive, sign of k decides sign of w
  if (k > 0) {
    res = vsatu/(1+d*k/2);
  } else {
    res = vsatu/(1-d*k/2);
  }
  // centripetal acceleration constraint:
  res = min(res, sqrt(vwmaxi/fabs(k)));
  // add obstacle constraints later on if needed
  return res;
}

typedef pair<double, double> Interval;
// acceleration constraints

// translational acceleration constraint
// atmax: max translational acceleration, +ve, cm/s^2
// dels: distance between this and old point, cm
Interval trans_acc_limits(double vwold, double vwmax, double vold, double atmax, double dels) {
  double vmin, vmax;
  // use curvature to find maximum allowed acceleration
  // using the relation:
  // (dv/dt)^2/(atmax)^2+(vwold)^2/(vwmax)^2 < 1
  // hence dv/dt < sqrt(1-(vwold/vwmax)^2)*atmax
  // and at = sqrt(1-(vwold/vwmax)^2)*atmax
  // make sure units are all correct!
  if (fabs(vwold/vwmax) > 1) {
      vwold = vwmax;
  }
//  cout << vwold << " herte" << vwmax << endl;
  assert(fabs(vwold/vwmax) <= 1.);
  double at = sqrt(1-(vwold/vwmax)*(vwold/vwmax))*atmax;
  // std::cout << "in trans acc, vwold and vwmax = " << vwold << vwmax << ", at = " << at;
  if (vold*vold > 2*atmax*dels)
    vmin = sqrt(vold*vold - 2*at*dels);
  else
    vmin = 0;
  vmax = sqrt(vold*vold + 2*at*dels);

//  // std::cout << "vold = " << vold << ", (min,max)= " << vmin << vmax;
  return Interval(vmin, vmax);
}

// rotational acceleration constraint
// awmax: maximum rotational acceleration, 1/s^2
vector<Interval> rot_acc_limits(double vold, double kold, double k, double dels,
  double awmax) {
  vector<Interval> ans;
  double v1, v2, v1_star, v2_star, v1_cap, v2_cap;
  if (k > 1e-5) {
    double term = (k+kold)*(k+kold)*vold*vold-8*k*awmax*dels;
    if (term < 0) {
      {
        double term = sqrt((k+kold)*(k+kold)*vold*vold+8*k*awmax*dels);
        v1 = 1/(2*k)*((kold-k)*vold+term);
        v2 = 1/(2*k)*((kold-k)*vold-term);
      }
      Interval i(v2, v1);
      ans.push_back(i);
      return ans;
    } else {
      {
        double term = sqrt((k+kold)*(k+kold)*vold*vold+8*k*awmax*dels);
        v1 = 1/(2*k)*((kold-k)*vold+term);
        v2 = 1/(2*k)*((kold-k)*vold-term);
      }
      {
        double term = sqrt((k+kold)*(k+kold)*vold*vold-8*k*awmax*dels);
        v1_star = 1/(2*k)*((kold-k)*vold+term);
        v2_star = 1/(2*k)*((kold-k)*vold-term);
      }
      Interval i1(v2, v2_star);
      Interval i2(v1_star, v1);
      ans.push_back(i1);
      ans.push_back(i2);
      return ans;
    }
  } else if (k < -1e-5) {
    double term = (k+kold)*(k+kold)*vold*vold+8*k*awmax*dels;
    if (term < 0) {
      {
        double term = sqrt((k+kold)*(k+kold)*vold*vold-8*k*awmax*dels);
        v1_star = 1/(2*k)*((kold-k)*vold+term);
        v2_star = 1/(2*k)*((kold-k)*vold-term);
      }
      Interval i(v1_star, v2_star);
      ans.push_back(i);
      return ans;
    } else {
      {
        double term = sqrt((k+kold)*(k+kold)*vold*vold+8*k*awmax*dels);
        v1 = 1/(2*k)*((kold-k)*vold+term);
        v2 = 1/(2*k)*((kold-k)*vold-term);
      }
      {
        double term = sqrt((k+kold)*(k+kold)*vold*vold-8*k*awmax*dels);
        v1_star = 1/(2*k)*((kold-k)*vold+term);
        v2_star = 1/(2*k)*((kold-k)*vold-term);
      }
      Interval i1(v1_star, v1);
      Interval i2(v2, v2_star);
      ans.push_back(i1);
      ans.push_back(i2);
      return ans;
    }
  } else {
    // k ~ 0
    if (kold > -1e-5 && kold < 1e-5) {
      // kold ~ 0
      Interval i(-numeric_limits<double>::infinity(),
        numeric_limits<double>::infinity());
      ans.push_back(i);
      return ans;
    } else {
      {
        v1_cap = -2*dels*awmax/(kold*vold)-vold;
        v2_cap = 2*dels*awmax/(kold*vold)-vold;
      }
      if (kold > 1e-5) {
        Interval i(v1_cap, v2_cap);
        ans.push_back(i);
        return ans;
      } else {
        Interval i(v2_cap, v1_cap);
        ans.push_back(i);
        return ans;
      }
    }
  }
}

vector<ProfileDatapoint> generateVelocityProfile(Spline &p, int numPoints, double vls, double vrs, double vle, double vre)
{

    // all calculations are done AFTER converting strategy coordinates to cm!
    assert(numPoints >= 2);
    double full = Integration::integrate(p, 0, 1);
    double vs = (vls+vrs)/2.;
    double ve = (vle+vre)/2.;
    //std::cout << vs << " " << ve << endl;
    assert(ve >= 0);
    vector<ProfileDatapoint> v(numPoints, ProfileDatapoint());
    double dels = full/(numPoints-1);

	alglib::spline1dinterpolant splineSU;
    Integration::computeSplineApprox(p, &splineSU);
    for (int i = 0; i < v.size(); i++) {
        double s = full/(numPoints-1)*(double)i;
        double u = Integration::getArcLengthParam(p, s, &splineSU, full);
        double k = p.k(u);
        //NOTE: hardcoding vsat here!!
        v[i].v = min(vmax_isolated(k, vsat), vsat);
        v[i].u = u;
        v[i].s = s;
    }
	
	// in case of negative starting velocity, adding 2 CP:
    // 1. at the point where bot goes from negative -> zero velocty, should be
    // at distance of -v^2/(2*a) whre a = max decelaration
    // 2. at the point where it reaches original starting point, but with positive velocity
    if (vs < 0) {
        double s = -vs*vs/atmax/2./10.;
        ProfileDatapoint dp;
        dp.v = 0;
        dp.s = s;
        dp.u = Integration::getArcLengthParam(p, dp.s, &splineSU, full);
        v.insert(v.begin()+1, dp);
        dp.v = -vs;
        dp.s = 0;
        dp.u = 0;
        v.insert(v.begin()+2, dp);
    }
	
    // forward consistency
    v[0].v = vs;
    for (int i = 1; i < v.size(); i++) {
        double vwold = v[i-1].v*v[i-1].v*p.k(v[i-1].u);
		assert(p.k(v[i-1].u) != 0);
        double vw = vwIntercept + vwSlope/p.k(v[i-1].u);
        if( vw < vwmax)
            vw = vwmax;
        v[i].v = min(v[i].v, trans_acc_limits(vwold, vwmax, v[i-1].v, atmax, dels).second);
    }
    // backward consistency
    v[v.size()-1].v = ve;
    for (int i = v.size()-2; i >= 0; i--) {
        double vwold = v[i+1].v*v[i+1].v*p.k(v[i+1].u);
		assert(p.k(v[i+1].u) != 0);
        double vw = vwIntercept + vwSlope/p.k(v[i+1].u);
        if( vw < vwmax)
            vw = vwmax;
        v[i].v = min(v[i].v, trans_acc_limits(vwold, vwmax, v[i+1].v, atmax, dels).second);
    }
    // set time to reach for each datapoint
    v[0].t = 0;
    for (int i = 1; i < v.size(); i++) {
        v[i].t = v[i-1].t + 2*dels/(v[i].v+v[i-1].v);
    }
    // std::cout << "profile:" ;
//    for (int i = 0; i< v.size(); i++) {
//        // std::cout << v[i].u << v[i].t << v[i].s << v[i].v;
//    }
    return v;
}

ProfileDatapoint::ProfileDatapoint(): u(0), v(0), s(0), t(0)
{

}

ProfileDatapoint::ProfileDatapoint(double u, double v, double s, double t): u(u), v(v), s(s), t(t)
{

}

bool ProfileDatapoint::operator<(const ProfileDatapoint &dp) const
{
    return t < dp.t;
}

}
