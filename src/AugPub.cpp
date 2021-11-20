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
#include <time.h>

using namespace std;
using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

int main(int argc, char**argv)
{
    double pain = 0.0, hurt = 0.0, status = 0.0;
    ros::init(argc, argv, "AugerCont");
        ros::NodeHandle n;
        ros::Rate loop_rate(69);

        ros::Publisher Testpath = n.advertise<std_msgs::Float32>("AugerToggle", 69);

        std_msgs::Float32 AugTask;

    while(ros::ok())
    {
        Testpath.publish(AugTask);
        
        ros::spinOnce();
        loop_rate.sleep();

        if (status == 0)
        AugTask.data = .3;
        if (status == 1)
        AugTask.data = -.3;
        pain++;
        if (pain > 600)
            pain = 0;
        if (pain == 0)
            status = 0;
        if (pain == 300)
            status = 1;
    }
    return 0;
}