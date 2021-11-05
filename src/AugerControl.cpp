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

#define LINEAR_ADJ 1
#define ANGULAR_ADJ 1
#define DRIVE_SCALE 1 // 25%

/*******************************************************************************
****     This node subscribes to the motor values set in ExcvLDrvPwr and 	****
****         ExcvRDrvPwr and sets the motors speeds respectively         	****
****     Subscribers:                                                    	****
****          std_msgs/Float32 ExcvLDrvPwr - left motor value            	****
****          std_msgs/Float32 ExcvRDrvPwr - right motor value              ****
****		  geometry_msgs/Twist cmd_vel   - tport left & right motor power****
*******************************************************************************/

class Listener
{
    public:
        void getAugerSpeed(const std_msgs::Float32 motorSpeed);
        void setAuger();
        float augerSpeed = 0;
        float gearRatio = 80;

        TalonSRX augerDrive = {DeviceIDs::AugerTal};
};

void Listener::getAugerSpeed(const std_msgs::Float32 motorSpeed)
{
    augerSpeed = motorSpeed.data * DRIVE_SCALE;
}

void Listener::setAuger()
{
	augerDrive.Set(ControlMode::PercentOutput, augerSpeed);
	
	ctre::phoenix::unmanaged::FeedEnable(100);	
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "AugerControl");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

   	phoenix::platform::can::SetCANInterface("can0");

    Listener listener;

   	ros::Subscriber motor_toggle_sub = n.subscribe("AugerToggle", 100, &Listener::getAugerSpeed, &listener);

    while (ros::ok())
	{
        listener.setAuger();

        int augerSpeed = listener.augerDrive.GetSensorCollection().GetQuadratureVelocity();
        int shaftRPM = 0.3*(augerSpeed/listener.gearRatio);
		string mssg = to_string(shaftRPM);

		ROS_INFO_STREAM("Msg: " << mssg);

		ros::spinOnce();
		loop_rate.sleep();
    }
}