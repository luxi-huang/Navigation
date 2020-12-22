/// \file
/// \brief:create_fake_diff_encoders;
///
/// PUBLISHERS:sensor_msgs/JointState (joint_state): publish wheels's joint_state
///
/// SUBSCRIBERS:geometry_msgs/Twist (cmd_vel);

#include "rigid2d/rigid2d.hpp"
#include "rigid2d/diff_drive.hpp"
#include "ros/ros.h"
#include <sstream>
#include "geometry_msgs/Twist.h"
#include <cstdlib>
#include <sensor_msgs/JointState.h>
#include <string>
#include <nav_msgs/Odometry.h>

using namespace std; 

class FakeDiffEncoder
{
private: 
  ros::Publisher joint_state_publisher;
  ros::Subscriber vel_subscriber;
  rigid2d::DiffDrive myRobot;
  string left_wheel_joint;
  string right_wheel_joint;
  string base_link;
  double wheel_base;
  double wheel_radius;
  rigid2d::Twist2D Twist_value;

public:
    FakeDiffEncoder(ros::NodeHandle &nh)
    {
      vel_subscriber = nh.subscribe("turtle1/cmd_vel",10, &FakeDiffEncoder::velCallback, this);
      joint_state_publisher = nh.advertise<sensor_msgs::JointState>("joint_states", 1000);

      nh.getParam("~left_wheel_joint", left_wheel_joint);
      nh.getParam("~right_wheel_joint",right_wheel_joint);

      nh.getParam("wheel_base",wheel_base);
      nh.getParam("wheel_radius",wheel_radius);

      // initial robot;
      rigid2d::Transform2D initPose;
      myRobot = rigid2d::DiffDrive(initPose, wheel_base, wheel_radius); 

      while(ros::ok())
      {
        rigid2d::WheelVelocities wheel_v;
        wheel_v = myRobot.twistToWheels(Twist_value);
        publish_joint_state(wheel_v);
        // ROS_INFO ("wheel_radius,%f",wheel_radius);
        // ROS_INFO("%s",left_wheel_joint.c_str());
        // ROS_INFO("fake_x %f",Twist_value.theta_dot);

        ros::spinOnce();
      }
    }  

  void velCallback(const geometry_msgs::Twist::ConstPtr & Twist)
  {
    Twist_value.vx = Twist->linear.x;
    Twist_value.vy = Twist->linear.y;
    Twist_value.theta_dot=Twist->angular.z;
  }

  void publish_joint_state(rigid2d::WheelVelocities v)
  {
    std::vector<std::string> joint_name_vector;
    sensor_msgs::JointState j_s;
    joint_name_vector.push_back("odometer/left_wheel_joint");
    joint_name_vector.push_back("odometer/right_wheel_joint");

    j_s.name.resize(joint_name_vector.size());
    j_s.position.resize(joint_name_vector.size());
    j_s.velocity.resize(joint_name_vector.size());

    j_s.name[0] = joint_name_vector[0];
    j_s.name[1] = joint_name_vector[1];
    j_s.header.stamp = ros::Time::now();
    j_s.velocity[0] = v.u1;
    j_s.velocity[1] = v.u2;
    joint_state_publisher.publish(j_s);
  }
};


int main(int argc, char **argv)
{
    // init the node
    ros::init(argc, argv, "fake_diff_encoders");
    ros::NodeHandle nh;
    FakeDiffEncoder encoder = FakeDiffEncoder(nh);

    ros::spin();
    return 0;
}