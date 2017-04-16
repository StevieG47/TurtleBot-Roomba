# TurtleBot Simple Walker

### Overview

- A ROS package with a simple walker algorithm for a TurtleBot to move like a Roomba vacuum, simulated in Gazebo. The robot will move forward until detecting an obstacle, turn in place, and continue moving forward.

- The included node publishes to the */cmd_vel_mux/input/teleop* to drive the robot (publishing to the */mobile_base/commands/velocity* topic would work as well). It also subscribes to the *.scan* topic to get sensor information.


### Dependencies
- ROS Indigo
- Gazebo
- catkin
- turtlebot_gazebo
- roscpp package



### How to Build
- Create the catkin workspace and build with:
```
mkdir catkin_ws
cd catkin_ws
mkdir src
cd src
git clone --recursive https://github.com/StevieG47/TurtleBot-Roomba
cd ..
catkin_make
```

### Running 
- To run the simulation, use the *turtleRoomba.launch* launch file.

```
roslaunch turtlebot_roomba turtleRoomba.launch
```

This launches gazebo with the TurtleBot in the *corridor.world* world. Also, a new terminal will open with current information about the TurtleBot. The distance to an object in front of the robot is printed, along with the current action, *Forward* or *Turn*.

The robot will move forward until detecting an obstacle close enough (threshold is .7) and then turn left in place until it is safe to move forward again. 


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

#### Bag File Playback
- The bag file can be played back using *rosbag play*. Gazebo should not be running for the playback. To playback, open a terminal and run roscore, then open another terminal and navigate to the *.ros* directory.
```
rosbag play File.bag
```

The node included in this repository can be run during the playback and will print the same distance/action messages as when the simulation was being recorded. In a new terminal, navigate to *catkin_ws*.
```
source devel/setup.bash
rosrun turtlebot_roomba roomba
```


