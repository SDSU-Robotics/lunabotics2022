#include "ctre/Phoenix.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/Twist.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "DeviceIDs.h"
#include "ctre/phoenix/motorcontrol/SensorCollection.h"
#include <iostream>
#include <string>

using namespace std;
using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

int main(int argc, char**argv)
{
    ros::init(argc, argv, "ManDrivingBase");
        ros::NodeHandle n;
        ros::Rate loop_rate(69);

        ros::Publisher Testpath = n.advertise<std_msgs::Float32>("LDrvPwr", 69);
        ros::Publisher Testpath = n.advertise<std_msgs::Float32>("RDrvPwr", 69);

        std_msgs::Float32 BackDrive;

    while(ros::ok())
    {
        Testpath.publish(BackDrive);
        
        ros::spinOnce();
        loop_rate.sleep();

        BackDrive.data = 0;
        
    }
    return 0;
}