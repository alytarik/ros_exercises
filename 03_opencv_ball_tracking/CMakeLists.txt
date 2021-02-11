cmake_minimum_required(VERSION 3.0.2)
project(ros_ball_tracking)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   myTime.msg
# )

## Generate services in the 'srv' folder
#add_service_files(
#  FILES
#  dateToDay.srv
#)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
#generate_messages(
#  DEPENDENCIES
#  std_msgs
#)

###################################
## catkin specific configuration ##
###################################
catkin_package(
 #INCLUDE_DIRS include
 LIBRARIES time_pubsub
 CATKIN_DEPENDS roscpp rospy std_msgs 
 #DEPENDS system_lib
)

###########
## Build ##
###########

find_package(OpenCV)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(ball_tracker src/ball_tracker.cpp)
target_link_libraries(ball_tracker ${catkin_LIBRARIES})

