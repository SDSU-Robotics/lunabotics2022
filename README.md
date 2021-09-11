# lunabotics2022

## Prerequisites

 1. Install necessary tools and utilities
     - `sudo apt install git`
 2. Install ROS Melodic
     - http://wiki.ros.org/melodic/Installation/Ubuntu
     - Perform full desktop installation
 3. Install ROS packages
     - `sudo apt install ros-melodic-joy`
 
## Setup
 1. Setup catkin workspace
     - `mkdir -p ~/catkin_ws/src`
     - `cd ~/catkin_ws/src`
     - `cd ~/catkin_ws``
     - `catkin_make`
     - `echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc`
     - `source ~/.bashrc`
 2. Clone repo into user directory `git clone https://github.com/SDSU-Robotics/lunabotics2022.git`.
 3. Navigate into repo `cd lunabotics2022`.

## Building
 1. `cd ~/catkin_ws`
 2. `catkin_make`
