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

add_executable(Izaktalker ${PROJECT_SOURCE_DIR}/src/Izaktalker.cpp)
target_link_libraries(Izaktalker ${catkin_LIBRARIES} Threads::Threads)

add_executable(Izaklistener ${PROJECT_SOURCE_DIR}/src/Izaklistener.cpp)
target_link_libraries(Izaklistener ${catkin_LIBRARIES} Threads::Threads)

add_executable(motorSpin ${PROJECT_SOURCE_DIR}/src/motorSpin.cpp)
target_link_libraries(motorSpin ${catkin_LIBRARIES} Threads::Threads)

target_link_libraries(motorSpin ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_Phoenix.a)
target_link_libraries(motorSpin ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCCI.a)
target_link_libraries(motorSpin ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixPlatformLinuxSocketCan.a)
target_link_libraries(motorSpin ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCanutils.a)


add_executable(LEDToggle ${PROJECT_SOURCE_DIR}/src/LEDToggle)
target_link_libraries(LEDToggle ${catkin_LIBRARIES} Threads::Threads)