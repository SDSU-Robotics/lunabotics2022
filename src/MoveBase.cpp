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

#define Drive_SCALE 0.5

//class to store variables and functions
class Listener
{
    public:

        Listener();
        
        //define functions to be used
        void getTwistSpeed(const geometry_msgs::Twist twist);
        void setMotorOutput();

        //variables to store data used to drive left and right motorcontrollers
        float leftPower = 0;
        float rightPower = 0;

        TalonSRX leftDrive = {DeviceIDs::ExcvDrvLTal};
        TalonSRX rightDrive = {DeviceIDs::ExcvDrvRTal};
};
//function to make both wheels spin in the same direction
Listener::Listener()
{
    rightDrive.SetInverted(true);
}

//function to use the data published by nav_stack and convert the data to motor input, then store the data
void Listener::getTwistSpeed(const geometry_msgs::Twist twist)
{
    leftPower = Drive_SCALE * twist.linear.x + Drive_SCALE * twist.angular.z;
    rightPower = Drive_SCALE * twist.linear.x - Drive_SCALE * twist.angular.z;
}

//function to send motor data to the motors
void Listener::setMotorOutput()
{
    leftDrive.Set(ControlMode::PercentOutput, leftPower);
    rightDrive.Set(ControlMode::PercentOutput, rightPower);

    ctre::phoenix::unmanaged::FeedEnable(100);
}

//main function
int main (int argc, char **argv)
{
    //startup ROS, required
    ros::init(argc, argv, "MoveBase");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    Listener listener;

    //connect cannable
    phoenix::platform::can::SetCANInterface("can0");

    //each time the nav_stack sends a message across this topic, call the function: getTwistSpeed().
    //The message is a "twist" message; therefore, the parameter of the function is 
    //getTwistSpeed(const geometry_msgs::Twist twist). This is defined above inside the listener class
    ros::Subscriber twistMsg = n.subscribe("cmd_vel", 100, &Listener::getTwistSpeed, &listener);

    std_msgs::Int32 leftPos;
    std_msgs::Int32 rightPos;

    ros::Publisher leftTick = n.advertise<std_msgs::Int32>("left_ticks", 100);
    ros::Publisher rightTick = n.advertise<std_msgs::Int32>("right_ticks", 100);

    //run this block of code as long as ROS is running
    while (ros::ok())
    {
        //call the function to send power to the motor controllers
        listener.setMotorOutput();

        leftPos.data = listener.leftDrive.GetSensorCollection().GetQuadraturePosition();
        rightPos.data = listener.rightDrive.GetSensorCollection().GetQuadraturePosition();

        leftTick.publish(leftPos);
        rightTick.publish(rightPos);

        //needed for ROS to work properly
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}