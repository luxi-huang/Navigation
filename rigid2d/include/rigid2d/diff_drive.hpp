#ifndef diff_drive_INCLUDE_GUARD_HPP
#define diff_drive_INCLUDE_GUARD_HPP
/// \file
/// \brief Library for two-dimensional rigid body transformations.

#include<iosfwd> // contains forward definitions for iostream objects
#include "cmath"
#include "rigid2d/diff_drive.hpp"

namespace rigid2d
{
  struct Pose
  {
    double theta = 0.0;
    double x = 0.0;
    double y = 0.0;
  };


  class DiffDrive
  {
  public:
      // /// \brief the default constructor creates a robot at (0,0,0), with a fixed wheel base and wheel radius
      // DiffDrive();
      //
      // /// \brief create a DiffDrive model by specifying the pose, and geometry
      // ///
      // /// \param pose - the current position of the robot
      // /// \param wheel_base - the distance between the wheel centers
      // /// \param wheel_radius - the raidus of the wheels
      // DiffDrive();
      //
      // /// \brief determine the wheel velocities required to make the robot
      // ///        move with the desired linear and angular velocities
      // /// \param twist - the desired twist in the body frame of the robot
      // /// \returns - the wheel velocities to use
      // /// \throws std::exception
      // WheelVelocities twistToWheels();
      //
      // /// \brief determine the body twist of the robot from its wheel velocities
      // /// \param vel - the velocities of the wheels, assumed to be held constant
      // ///  for one time unit
      // /// \returns twist in the original body frame of the
      // wheelsToTwist(WheelVelocities vel);
      //
      // /// \brief Update the robot's odometry based on the current encoder readings
      // /// \param left - the left encoder angle (in radians)
      // /// \param right - the right encoder angle (in radians)
      // void updateOdometry();
      //
      // /// \brief update the odometry of the diff drive robot, assuming that
      // /// it follows the given body twist for one time  unit
      // /// \param cmd - the twist command to send to the robot
      // void feedforward();
      //
      // /// \brief get the current pose of the robot
      // Twist2D#include "rigid2d/diff_drive.hpp" pose();
      //
      // /// \brief get the wheel speeds, based on the last encoder update
      // /// \returns the velocity of the wheels, which is equivalent to
      // /// displacement because \Delta T = 1
      // WheelVelocities wheelVelocities() const
      //
      // /// \brief reset the robot to the given position/orientation
      // void reset(rigid2d::Twist2D ps);

  };

}

#endif
