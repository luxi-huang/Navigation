# ME495 Sensing, Navigation, and Machine Learning

Author: Luxi Huang

### Project Overview:
This totally-from-scratch project involved modeling a Turtlebot3 in Gazebo and using Differential Drive Kinematics to perform Odometry calculations. The Gazebo Plugin was developed to emulate the low-level interface on the real Turtlebot3 for the ability to develop high-fidelity code in simulation. I also implemented landmark detection on the Turtlebot3’s LIDAR, and used these features to perform EKF SLAM with Unknown Data Association.


The core project components are:

- rigid2d library containing 2D Lie Group operations for Transforms, Vectors and Twists as well as differential drive robot kinematics for odometry updates.
- nuturtle_description: houses the description of a differential drive robot with a caster wheel for support.
- nuturtle_robot: interfaces with the real Turtlebot3’s low-level controls such as setting wheel speeds and reading sensors.
- nuturtle_gazebo: contains a Gazebo Plugin to emulate the Turtlebot3’s low-level controls in Gazebo for the ability to develop in simulation.
- nuslam: library containing LIDAR feature detection methods and EKF SLAM implementation with Unknown Data Association.
