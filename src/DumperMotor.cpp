#include "ros/ros.h"
#include "iostream"

#include <sensor_msgs/Joy.h>
#include "std_msgs/Float32.h"
#include "JoyMap.h"
#include "DeviceIDs.h"

#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "ctre/phoenix/motorcontrol/SensorCollection.h"

using namespace std;

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

#define DRIVE_SCALE 0.1

bool buttons[12] = { 0 };
double axes[6] = { 0 };

TalonSRX dumpMotor = {DeviceIDs::dumpMotor};

void JoyListener(const sensor_msgs::Joy::ConstPtr& Joy)
{
    for (int i = 0; i < 12; i++)
        buttons[i] = Joy->buttons[i];
    
    for (int i = 0; i < 6; i++)
        axes[i] = Joy->axes[i];
}


void SpinMotor (bool cw, bool ccw, bool spin)
{
    if(cw || ccw)
        spin = true;
    
    if (!spin)
    {
        dumpMotor.Set(ControlMode::PercentOutput, 0);
    }
    else if(spin && cw)
    {
        dumpMotor.Set(ControlMode::PercentOutput, 1);
        spin = false;
    }
    else if (spin && ccw)
    {
        dumpMotor.Set(ControlMode::PercentOutput, -1);
        spin = false;
    }

    ctre::phoenix::unmanaged::FeedEnable(100);
}
void SpinMotorCCW (int toggleData)
{
    dumpMotor.Set(ControlMode::PercentOutput, toggleData);

    ctre::phoenix::unmanaged::FeedEnable(100);
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "motorspin");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    phoenix::platform::can::SetCANInterface("can0");

    ros::Subscriber joySub = n.subscribe("joy", 100, JoyListener);

    int CW_spin = {JoyMap::CW};
    int CCW_spin = {JoyMap::CCW};

    bool buttonCurrent = false;
    bool buttonPress = false;
    bool spinning = false;

    while (ros::ok())
    {
        
        SpinMotor(buttons[CW_spin], buttons[CCW_spin], spinning);
        
        ros::spinOnce();
        loop_rate.sleep();

    }

    return 0;
}