#add package server to /etc/apt/sources.list.d/ros-latest.list
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list';

#keys
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654;

#update
sudo apt-get update && sudo apt-get upgrade -y;

#install ros packages
sudo apt-get install ros-melodic-desktop-full;


#additional packages
apt-cache search ros-melodic;


#search packadge
apt-cache search ros-melodic;

#install rosdep(dependencies)
sudo rosdep init;
rosdep update;

rostopic list;
#/rosout
#/rosout_agg
#
rosservice list;
#/rosout/get_loggers
#/rosout/set_logger_level

#
source ~/catkin_ws/devel/setup.bash;

#start ros server
roscore &;

#start ros server with emptymap
rosrun gazebo_ros gazebo;

#start ros client with world
rosrun gazebo_ros gazebo world.world;


#launch woth px4 autopilot
roslaunch mavros px4.launch world.world fcu_url:="udp://:14540@127.0.0.1:14557" 

####install catkin
source /opt/ros/melodic/setup.bash;
#create and build a catkin workspace:

#make catkin
$ mkdir -p ~/catkin_ws/src;
$ cd ~/catkin_ws/;
$ catkin_make;

#run head cmake
:~/catkin_ws/src$ cmake . ;

#create cmake
catkin_create_pkg beginner_tutorials std_msgs rospy roscpp;

#check catkin /home/youruser/catkin_ws/src:/opt/ros/kinetic/share;
echo $ROS_PACKAGE_PATH;
