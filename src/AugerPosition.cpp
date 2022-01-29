#include "ctre/Phoenix.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
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

// Functions


void AugerUp(const std_msgs::Int32 augerRaise)
{
    int motorValue = augerRaise.data;

    if(motorValue < 0){
        motorValue = 0;
    }

    augerPostionTalon.Set(ControlMode::PercentOutput, motorValue);
	
	ctre::phoenix::unmanaged::FeedEnable(100);
}

void AugerDown(const std_msgs::Int32 augerLower)
{
    int motorValue = augerLower.data;

    if(motorValue < 0){
        motorValue = 0;
    }
    augerPostionTalon.Set(ControlMode::PercentOutput, motorValue);

	ctre::phoenix::unmanaged::FeedEnable(100);
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "AugerPosition");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    phoenix::platform::can::SetCANInterface("can0");
    
    //Function Calling

    ros::Subscriber augerRaise = n.subscribe("Auger_Raise", 100, AugerUp);
    ros::Subscriber augerLower = n.subscribe("Auger_Lower", 100, AugerDown);
    
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
        
}