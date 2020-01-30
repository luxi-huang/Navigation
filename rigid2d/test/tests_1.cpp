#include "rigid2d/rigid2d.hpp"
#include <ros/ros.h>
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include <fstream>

// using namespace std;
using namespace rigid2d;

// TEST(TestSuite, test)
// {
//   struct Vector2D v;
//
//   // std::cout << "enter 1 for v.x\n";
//   ROS_INFO ("enter 1 for v.x\n");
//   std::cin >> v.x;
//   // std::cout << "enter 1 for v.y\n";
//   ROS_INFO ("enter 1 for v.y\n");
//   std::cin >> v.y;
//
//   std::stringstream buffer;
//   buffer << "v :"<<v.x<<","<<v.y;
//   ASSERT_EQ(buffer.str(),"v :1,1");
// }



TEST(TestSuite, test1)
{
  int a;
  ROS_INFO ("enter 1");
  a = almost_equal(0, 0);
  ASSERT_EQ(1,a) << "is zero faild";
}

TEST(TestSuite, test2)
{
  int a;
  a = almost_equal(0.001, 0.005, 1.0e-2);
  ASSERT_EQ(1,a)<< "is_zero failed" ;
}

TEST(TestSuite, test3)
{
  int a;
  a = almost_equal(deg2rad(0.0), 0.0);
  ASSERT_EQ(1,a) << "deg2rad failed";
}

TEST(TestSuite, test4)
{
  int a;
  a = almost_equal(rad2deg(0.0), 0.0);
  ASSERT_EQ(1,a) << "rad2deg) failed";
}


TEST(TestSuite, test5)
{
  int a;
  a = almost_equal(deg2rad(rad2deg(2.1)), 2.1);
  ASSERT_EQ(1,a) << "deg2rad failed";
}

// Test identity Transform2D;
TEST(TestSuite, test6)
{
  Transform2D I;
  I = Transform2D();

  std::stringstream buffer;
  buffer << "I : "<<I;
  ASSERT_EQ(buffer.str(),"I : degree0 dx 0dy 0");
}

//Test Transform2D Tab(v_ab);
TEST(TestSuite, test7)
{
  struct Vector2D v_ab;
  v_ab.x =1;
  v_ab.y =1;
  Transform2D Tab(v_ab);

  std::stringstream buffer;
  buffer << "Tab : "<<Tab;
  ASSERT_EQ(buffer.str(),"Tab : degree0 dx 1dy 1");
}

// test Transform2D Tab(radians_ab)
TEST(TestSuite, test8)
{
  struct Vector2D v_ab;
  double degree_ab, radians_ab;
  v_ab.x =1;
  v_ab.y =1;
  degree_ab=30;
  radians_ab = deg2rad(degree_ab);
  Transform2D Tab(radians_ab);
  std::stringstream buffer;
  buffer << "Tab : "<<Tab;
  ASSERT_EQ(buffer.str(),"Tab : degree30 dx 0dy 0");
}

//test Transform2D Tab(v_ab, radians_ab);
TEST(TestSuite, test9)
{
  struct Vector2D v_ab;
  double degree_ab, radians_ab;
  v_ab.x =1;
  v_ab.y =1;
  degree_ab=30;
  radians_ab = deg2rad(degree_ab);
  Transform2D Tab(v_ab, radians_ab);

  std::stringstream buffer;
  buffer << "Tab : "<<Tab;
  ASSERT_EQ(buffer.str(),"Tab : degree30 dx 1dy 1");
}


// test inv;
TEST(TestSuite, test10)
{
  struct Vector2D v_ab;
  double degree_ab, radians_ab;
  v_ab.x =1;
  v_ab.y =1;
  degree_ab=30;
  radians_ab = deg2rad(degree_ab);
  Transform2D Tab(v_ab, radians_ab);
  Transform2D Tba;

  Tba = Tab.inv();
  std::stringstream buffer;
  buffer << "Tba : "<<Tba;
  ASSERT_EQ(buffer.str(),"Tba : degree-30 dx -1.36603dy -0.366025");
}

//test operator *=
TEST(TestSuite, test11)
{
  struct Vector2D v_ab;
  double degree_ab, radians_ab;
  v_ab.x =1;
  v_ab.y =1;
  degree_ab=30;
  radians_ab = deg2rad(degree_ab);
  Transform2D Tab(v_ab, radians_ab);

  Transform2D I;
  I = Transform2D();

  Tab *= I;
  std::stringstream buffer;
  buffer << "Tab : "<<Tab;
  ASSERT_EQ(buffer.str(),"Tab : degree30 dx 1dy 1");
}

//Test *
TEST(TestSuite, test12)
{
  struct Vector2D v_ab, v_bc;
  double degree_ab, radians_ab,  degree_bc, radians_bc;
  v_ab.x =1;
  v_ab.y =1;
  degree_ab=30;
  radians_ab = deg2rad(degree_ab);
  Transform2D Tab(v_ab, radians_ab);

  v_bc.x =2;
  v_bc.y =1;
  degree_bc=60;
  radians_bc = deg2rad(degree_bc);
  Transform2D Tbc(v_bc, radians_bc);
  Transform2D Tac;
  Tac = Tab*Tbc;

  std::stringstream buffer;
  buffer << "Tac : "<<Tac;
  ASSERT_EQ(buffer.str(),"Tac : degree90 dx 2.23205dy 2.86603");
}

// test operatpr ()
TEST(TestSuite, test13)
{
  struct Vector2D v_ab, v_bc, v, va;
  double degree_ab, radians_ab,  degree_bc, radians_bc;
  v_ab.x =1;
  v_ab.y =1;
  degree_ab=30;
  radians_ab = deg2rad(degree_ab);
  Transform2D Tab(v_ab, radians_ab);

  v_bc.x =2;
  v_bc.y =1;
  degree_bc=60;
  radians_bc = deg2rad(degree_bc);
  Transform2D Tbc(v_bc, radians_bc);
  Transform2D Tac;
  Tac = Tab*Tbc;

  v.x =1;
  v.y =2;

  va = Tac(v);

  std::stringstream buffer;
  buffer << "va : "<<va.x<<","<<va.y;
  ASSERT_EQ(buffer.str(),"va : 0.232051,3.09808");
}



TEST(TestSuite, test14)
{
  struct Vector2D v;

  // std::cout << "enter 1 for v.x\n";
  ROS_INFO ("enter 1 for v.x\n");
  std::cin >> v.x;
  // std::cout << "enter 1 for v.y\n";
  ROS_INFO ("enter 1 for v.y\n");
  std::cin >> v.y;

  std::stringstream buffer;
  buffer << "v :"<<v.x<<","<<v.y;
  ASSERT_EQ(buffer.str(),"v :1,1");
}

// integrate twist test;
TEST(TestSuite, test15)
{
  Twist2D tw1;
  Vector2D v;
  tw1.vx = 1;
  tw1.vy = 2;
  v = intergrateTwist(tw1);

  std::stringstream buffer;
  buffer << "v :"<<v.x<<","<<v.y;
  ASSERT_EQ(buffer.str(),"v :1,1");

}




int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "tester");
  ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}
