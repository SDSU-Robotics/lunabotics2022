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

add_executable(Odometry ${PROJECT_SOURCE_DIR}/Odometry/odometry.cpp)
target_link_libraries(Odometry ${catkin_LIBRARIES})
add_executable(tf_broadcaster ${PROJECT_SOURCE_DIR}/robot_setup_tf/src/tf_broadcaster.cpp)
add_executable(tf_listener ${PROJECT_SOURCE_DIR}/robot_setup_tf/src/tf_listener.cpp)
target_link_libraries(tf_broadcaster ${catkin_LIBRARIES})
target_link_libraries(tf_listener ${catkin_LIBRARIES})


add_executable(laserScan ${PROJECT_SOURCE_DIR}/Sensor/laserScan.cpp)
#add_executable(landonHeader ${PROJECT_SOURCE_DIR}/Sensor/landonHeader.cpp)
target_link_libraries(laserScan ${catkin_LIBRARIES})



