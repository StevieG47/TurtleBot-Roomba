# TurtleBot3 Simple Walker

### Overview

- A ROS package with a simple walker algorithm for a TurtleBot3 to move like a Roomba vacuum, simulated in Gazebo. The robot will move forward until detecting an obstacle, turn in place, and continue moving forward.

- The included node publishes to the */cmd_vel* to drive the robot (publishing to the */mobile_base/commands/velocity* topic would work as well). It also subscribes to the */scan* topic to get sensor information.


### Dependencies
- ROS Melodic
- Gazebo
- catkin
- turtlebot3_gazebo
- roscpp 
- geometry_msgs 



### How to Build
- Create the catkin workspace and build with:
```
mkdir catkin_ws
cd catkin_ws
mkdir src
cd src
git clone --recursive https://github.com/adbdwai/turtlebot3_roomba
cd ..
catkin_make
```

### Running 
- To run the simulation, use the *turtleRoomba.launch* launch file.

```
source devel/setup.bash
roslaunch turtlebot_roomba turtleRoomba.launch
```

This launches gazebo with the TurtleBot in the *corridor.world* world. Also, a new terminal will open with current information about the TurtleBot. The distance to an object in front of the robot is printed, along with the current action, *Forward* or *Turn*.

![gazebo](https://cloud.githubusercontent.com/assets/25371934/25075042/f3c66560-22d8-11e7-8931-960d3e02f60c.JPG)

The robot will move forward until detecting an obstacle close enough (threshold is .7) and then turn left in place until it is safe to move forward again. 

![dist-action](https://cloud.githubusercontent.com/assets/25371934/25075048/0d0eaf0a-22d9-11e7-80d4-887f0f7be8f4.JPG)


### Recording Bag Files
- By default, the launch file will not record a bag file. Recording can be enabled by adding a *startRecord:=true* argument to the launch command.
```
roslaunch turtlebot_roomba turtleRoomba.launch startRecord:=true
```

This will be the run the same as described previously, but a bag file *File.bag* will be recorded. Ctrl+C in the terminal where the roslaunch command was done will stop the simulation and recording. The bag file will be saved in the *.ros* directory, not the current directory.



#### Bag File Info
- Information can be seen about the recording using *rosboag info*. All topics will be recorded except /camera/* topics.

To inspect the bag file, navigate to the *.ros* directory.
```
rosbag info File.bag
```

![rosbag-info](https://cloud.githubusercontent.com/assets/25371934/25075098/27608ada-22da-11e7-9761-ccf6d07c3de4.JPG)


#### Bag File Playback
- The bag file can be played back using *rosbag play*. Gazebo should not be running for the playback. To playback, open a terminal and run roscore, then open another terminal and navigate to the *.ros* directory. The sensor data will be published again like when the simulation was running.
```
rosbag play File.bag
```


