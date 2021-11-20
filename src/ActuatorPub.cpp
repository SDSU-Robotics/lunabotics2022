#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "DeviceIDs.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"

using namespace std;
using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

int main(int argc, char**argv)
{
    ros::init(argc, argv, "ActPub");
        ros::NodeHandle n;
        ros::Rate loop_rate(69);

        ros::Publisher Testpath = n.advertise<std_msgs::Float32>("TrencherPos", 69);

        std_msgs::Float32 Actuation;

    while(ros::ok())
    {
        Testpath.publish(Actuation);
        
        ros::spinOnce();
        loop_rate.sleep();

        Actuation.data = .4;
    }
    return 0;
}