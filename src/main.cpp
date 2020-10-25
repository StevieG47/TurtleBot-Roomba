/* MIT License
 Copyright (c) 2017 Steven Gambino
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 * @copyright Copyright 2017 Steven Gambino
 * @file main.cpp
 * @author Steven Gambino
 * @brief Node to move turtlebot like a roomba, move until obstacles, then turn
 *
 */
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <ros/console.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Roomba.h"

int main(int argc, char **argv) {
// initiate node
  ros::init(argc, argv, "roomba");
  ros::NodeHandle n;
  Roomba bot;

// rate
  ros::Rate loop_rate(10);

// create publisher roombaPub on geometry_msgs::Twist. Twist is math for linear/angular velocity. Topic is /cmd_vel_mux/input/teleop, Can also pusblish to /mobile_base/commands/velocity
// ros::Publisher roombaPub = n.advertise < geometry_msgs::Twist> ("/mobile_base/commands/velocity", 1);
  ros::Publisher roombaPub = n.advertise < geometry_msgs::Twist
      > ("/cmd_vel", 1000);

// SUBSCRIBE TO /scan to get info about sensor.
// ros::Subscriber subScan = n.subscribe < sensor_msgs::LaserScan>("/scan",10,&AutoExp::processLaserScan,this);
  ros::Subscriber subScan = n.subscribe("/scan", 100, &Roomba::AutoExp, &bot);  // subscriber

  int count = 0;
  while (ros::ok()) {
    // make input a Twist variable
    geometry_msgs::Twist input;

// Check for obstacle
    if (bot.checkObstacle(bot.smallest)) {
      // turn
      // make angular z positive
      input.linear.x = 0;
      input.linear.y = 0;
      input.linear.z = 0;
      input.angular.x = 0;
      input.angular.y = 0;
      input.angular.z = .5;

      // Print that we are turning
      if (bot.smallest > .00001) {
        ROS_INFO_STREAM("Dist: " << bot.smallest << ", Turn");
      }
    } else {
// move forward
// make linear x velocity positive
      if (bot.smallest > 0) {
        input.linear.x = .15;
        input.linear.y = 0;
        input.linear.z = 0;
        input.angular.x = 0;
        input.angular.y = 0;
        input.angular.z = 0;
        if (bot.smallest < 100) {
          ROS_INFO_STREAM("Dist: " << bot.smallest << ", Forward");
        }
      }
    }

    // When starting up dont move
    if (bot.smallest < .00001 || bot.smallest > 99) {
      input.angular.z = 0;
      input.linear.x = 0;
      ROS_INFO_STREAM("Idle");
    }

// publish to cmd_vel
    roombaPub.publish(input);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
