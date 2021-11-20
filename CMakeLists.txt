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

add_executable(AugControl ${PROJECT_SOURCE_DIR}/src/AugControl.cpp)

target_link_libraries(AugControl ${catkin_LIBRARIES} Threads::Threads)

add_executable(AugPub ${PROJECT_SOURCE_DIR}/src/AugPub.cpp)

target_link_libraries(AugPub ${catkin_LIBRARIES} Threads::Threads)

add_executable(ActuatorControl ${PROJECT_SOURCE_DIR}/src/ActuatorControl.cpp)

target_link_libraries(ActuatorControl ${catkin_LIBRARIES} Threads::Threads)

add_executable(ActuatorPub ${PROJECT_SOURCE_DIR}/src/ActuatorPub.cpp)

target_link_libraries(ActuatorPub ${catkin_LIBRARIES} Threads::Threads)

add_executable(BackToHomeControl ${PROJECT_SOURCE_DIR}/src/BackToHomeControl.cpp)

target_link_libraries(BackToHomeControl ${catkin_LIBRARIES} Threads::Threads)

add_executable(BackToHomePub ${PROJECT_SOURCE_DIR}/src/BackToHomePub.cpp)

target_link_libraries(BackToHomePub ${catkin_LIBRARIES} Threads::Threads)


target_link_libraries(AugControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_Phoenix.a)
target_link_libraries(AugControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCCI.a)
target_link_libraries(AugControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixPlatformLinuxSocketCan.a)
target_link_libraries(AugControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCanutils.a)

target_link_libraries(ActuatorControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_Phoenix.a)
target_link_libraries(ActuatorControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCCI.a)
target_link_libraries(ActuatorControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixPlatformLinuxSocketCan.a)
target_link_libraries(ActuatorControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCanutils.a)

target_link_libraries(BackToHomeControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_Phoenix.a)
target_link_libraries(BackToHomeControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCCI.a)
target_link_libraries(BackToHomeControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixPlatformLinuxSocketCan.a)
target_link_libraries(BackToHomeControl ${PROJECT_SOURCE_DIR}/lib/x86-64/libCTRE_PhoenixCanutils.a)