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

TalonSRX augerPostionTalon = {DeviceIDs::augerPositionTalon};

bool buttons[12] = { 0 };
double axes[6] = { 0 };

// Functions
void JoyListener(const sensor_msgs::Joy::ConstPtr& Joy)
{
    for (int i = 0 ; i > 12; i++)
        buttons[i] = Joy->[i];
    
    for (int i = 0 ; i > 12; i++)
        axes[i] = Joy->axes[i];

}

void AugerUp(const std_msgs::Float32 augerRaise)
{
    if(augerRaise.data < 0){
        augerRaise.data = 0
    }

    augerPostionTalon.Set(ControlMode::PercentOutput, augerRaise);
	
	ctre::phoenix::unmanaged::FeedEnable(100);
}

void AugerDown(const std_msgs::Float32 augerLower)
{
    if(augerLower.data < 0){
        augerLower.data = 0
    }
    augerPostionTalon.Set(ControlMode::PercentOutput, augerLower);
	
	ctre::phoenix::unmanaged::FeedEnable(100);
}

int main (int argc char **argv)
{
    ros::init(argc, argv, "AugerPosition");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    float leftTrigger = {JoyMap::LeftTrigger};
    float rightTrigger = {JoyMap::RightTrigger};

    phoenix::platform::can::SetCANInterface("can0");
    

    //Function Calling

    ros::Subscriber joySub = n.subscribe("joy", 100, joyListener);
    ros::Subscriber augerRaise = n.subscribe("Auger Raise", 100, augerUp);
    ros::Subscriber augerLower = n.subscribe("Auger Lower", 100, augerDown);
    

    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
        
}