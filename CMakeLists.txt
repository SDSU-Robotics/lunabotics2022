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

add_executable(ManualDriveController ${PROJECT_SOURCE_DIR}/src/ManualDriveController.cpp)
add_executable(ManualDriveBase ${PROJECT_SOURCE_DIR}/src/ManualDriveBase.cpp)
add_executable(AugerControl ${PROJECT_SOURCE_DIR}/src/AugerControl.cpp)
add_executable(MPU9250 ${PROJECT_SOURCE_DIR}/src/MPU9250.cpp)

target_link_libraries(ManualDriveController ${catkin_LIBRARIES} Threads::Threads)
target_link_libraries(ManualDriveBase ${catkin_LIBRARIES} Threads::Threads)
target_link_libraries(AugerControl ${catkin_LIBRARIES} Threads::Threads)
target_link_libraries(MPU9250 ${catkin_LIBRARIES} Threads::Threads)


target_link_libraries(ManualDriveBase ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_Phoenix.a)
target_link_libraries(ManualDriveBase ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCCI.a)
target_link_libraries(ManualDriveBase ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixPlatformLinuxSocketCan.a)
target_link_libraries(ManualDriveBase ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCanutils.a)

target_link_libraries(AugerControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_Phoenix.a)
target_link_libraries(AugerControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCCI.a)
target_link_libraries(AugerControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixPlatformLinuxSocketCan.a)
target_link_libraries(AugerControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCanutils.a)

target_link_libraries(MPU9250 ${PROJECT_SOURCE_DIR}/lib/arduino-1.8.16/hardware/arduino/avr/libraries/Wire/src/Wire.h)

