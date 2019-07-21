Hey, guys heres instructions to run this simualtion.

first you need to download the husky robot.

Theres instructions to do it here: http://wiki.ros.org/husky_gazebo/Tutorials/Simulating%20Husky
but basically you just run these two commands:

sudo apt-get install ros-kinetic-husky-simulator

export HUSKY_GAZEBO_DESCRIPTION=$(rospack find husky_gazebo)/urdf/description.gazebo.xacro


Then go to our group drive and download the file hallway1.world.  Place this file in your /usr/share/gazebo-7/worlds/ folder by going to that directory and running the command:

cp <path>/hallway1.world .


If you havent already, create a catkin workspace by typing

mkdir -p catkin_ws/src from you home directory or whereever you want to put it.

in the catkin_ws directory type:

catkin build

to build your workspace, then

source devel/setup.bash

to source your workspace

then copy or clone the repository into the src folder.

Alternatively you can clone the repository into another folder and the symbollically link it into the src folder by typeing:

ln -s <path>/<repository>

from the src directory.  I like to do this cause then u can unlink it later so you dont clutter up your workspace

finally build and source your workspace again from the catkin_ws directory

catkin build
source devel/setup.bash

the run the launch file by typing 

roslaunch husky_highlevel_controller husky_highlevel_controller.launch and the simulation should run in gazebo and rviz

to see stuff in rviz you must set fixed frame to odom.  Then select add, go to the topics tab, find the /scan topic, and select Laser_scan, and then click ok.  zoom way out and you should see the lazer dots on the wall.  Its helpful to increase the size from .01 to .1

Let me know if this works or if you have problems, I just kinda typed these instructions from memory without testing so there will likey be problems.
