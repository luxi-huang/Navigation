#include "rigid2d/diff_drive.hpp"
#include "rigid2d/rigid2d.hpp"
#include <iostream>
#include "cmath"
#include <cstdlib> //c standard library

namespace rigid2d{

DiffDrive::DiffDrive(){
  x = 0.0;
  y = 0.0;
  theta = 0.0;
  whe_base = 4.0;
  whe_radius = 2.0;
  L = 5.0;
}

DiffDrive::DiffDrive(const Pose & p,double wheel_base, double wheel_radius){
  x = p.x;
  y = p.y;
  theta = p.theta;
  whe_base = wheel_base;
  whe_radius = wheel_radius;
}

WheelVelocities DiffDrive::twistToWheels(Twist2D t){
  WheelVelocities u;
  // double D = whe_base/2.0;
  // mine orgianl
  // u.u1 = (1.0/whe_radius)*((-D)*t.theta_dot + t.vx);
  // u.u2 = (1.0/whe_radius)*((D)*t.theta_dot + t.vx);
  //new
  // u.u1 = -(whe_base/(2.0*whe_radius))*t.theta_dot+(1.0/whe_radius)*t.vx;
  // u.u2 = (whe_base/(2.0*whe_radius))*t.theta_dot+(1.0/whe_radius)*t.vx;
  //lastest
  u.u1 = (2.0*t.vx-t.theta_dot*whe_base)/(2*whe_radius);
  u.u2 = (2.0*t.vx+t.theta_dot*whe_base)/(2*whe_radius);

  u.u3 = u.u2;
  u.u4 = u.u1;
  return u;
}

Twist2D DiffDrive::wheelsToTwist(WheelVelocities vel){
  Twist2D t;
  // double D = whe_base/2.0;
  // mine original
  // double r = whe_radius/2.0;
  // t.theta_dot = ((-1/(D+L))*vel.u1 + (1/(D+L))*vel.u2 + (1/(D+L))*vel.u3 - (1/(D+L))*vel.u4)*(whe_radius/4);
  // t.vx = vel.u1 + vel.u2 + vel.u3 + vel.u4;
  // t.vy =-vel.u1 + vel.u2 - vel.u3 + vel.u4;

  // fiexed
  // t.vx = (vel.u1+vel.u2)*r;
  // t.theta_dot = (vel.u2/D-vel.u1/D)*r;
  // t.vy = 0;

  // latest
  t.theta_dot = (vel.u2-vel.u1)*whe_radius/whe_base;
  t.vx = (vel.u1+vel.u2)*whe_radius/2;
  t.vy = 0;



  return t;
}

void DiffDrive::updateOdometry(double left_radians, double right_radians){
  double R_D,L_D,D_T = 0;
  R_D = whe_radius*right_radians;
  L_D = whe_radius*left_radians;
  theta += (R_D -L_D)/1.0/whe_base;
  D_T = (R_D + L_D)/2.0;
  x = -(D_T)*sin(theta);
  y = (D_T)*cos(theta);
}

void DiffDrive::feedforward(Twist2D cmd,double ttime){
  double new_theta;
  new_theta = cmd.theta_dot* ttime + theta;
  theta = normalize_angle(new_theta);
  // std::cout<<"theta"<< theta<<"/n";
  // double linear_velocity = sqrt(pow(cmd.vx,2)+pow(cmd.vy,2));
  double linear_velocity = cmd.vx;
  x += linear_velocity*cos(theta)*ttime;
  y += linear_velocity*sin(theta)*ttime;
  // std::cout<<"x"<< x<< "   ";
}
//
Pose DiffDrive::pose(){
  Pose p;
  p.x = x;
  p.y = y;
  p.theta = theta;
  return p;
}

WheelVelocities DiffDrive::wheelVelocitie(double delta_radians_L, double delta_radians_R) const {
  WheelVelocities u;
  double R_D = delta_radians_L*whe_radius;
  double L_D = delta_radians_R*whe_radius;
  u.u1 = R_D;
  u.u2 = L_D;
  u.u3 = u.u3;
  u.u4 = u.u1;
  return u;
}

std::ostream & operator<<(std::ostream & os, const Pose & pose){
  os << "Pose_theta " << pose.theta << " x " << pose.x << "y "<< pose.y;
  return os;
}

std::istream & operator>>(std::istream & is, Pose & pose){
  is >> pose.theta;
  is >> pose.x;
  is >> pose.y;
  return is;
}

std::ostream & operator<<(std::ostream & os, const  WheelVelocities & wheel_v){
  os << "u1 " << wheel_v.u1 << " u2 " << wheel_v.u2 << "u3 "<< wheel_v.u3 << "u4 "<< wheel_v.u4;
  return os;
}

std::istream & operator>>(std::istream & is, WheelVelocities & wheel_v){
  is >> wheel_v.u1;
  is >> wheel_v.u2;
  is >> wheel_v.u3;
  is >> wheel_v.u4;
  return is;
}

}
