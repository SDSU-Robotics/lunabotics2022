# Project's name
PROJECT (lunabotics2022)

# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.1)

add_definitions(-std=c++11)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(catkin REQUIRED)
find_package (Threads REQUIRED)
find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	sensor_msgs
	laser_geometry
	tf2
	tf2_ros
	geometry_msgs
	tf
	nav_msgs
)

catkin_package()

include_directories (src include ${catkin_INCLUDE_DIRS})