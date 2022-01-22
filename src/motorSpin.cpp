#include "ros/ros.h"
#include "iostream"

#include <sensor_msgs/Joy.h>
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

bool buttons[12] = { 0 };
double axes[6] = { 0 };

TalonSRX motor = {DeviceIDs::motor};

void JoyListener(const sensor_msgs::Joy::ConstPtr& Joy)
{
    for (int i = 0; i < 12; i++)
        buttons[i] = Joy->buttons[i];

    for (int i = 0; i < 6; i++)
        axes[i] = Joy->axes[i];
}

int Toggle(const bool b, bool &current, bool &on)
{
    int toggleData;
    bool prev = current;
    current = b;

    if(prev && !current)
        on = !on;

    if(on)
        toggleData = 1;

    else 
        toggleData = 0;

    return toggleData;
}

void SpinMotor (int toggleData)
{
    motor.Set(ControlMode::PercentOutput, toggleData);

    ctre::phoenix::unmanaged::FeedEnable(100);
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "motorspin");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    phoenix::platform::can::SetCANInterface("can0");

    ros::Subscriber joySub = n.subscribe("joy", 100, JoyListener);

    int toggleButton = {JoyMap::toggle};
    bool buttonCurrent = false;
    bool buttonPress = false;
    
    while(ros::ok())
    {
        int toggleData = Toggle(buttons[toggleButton], buttonCurrent, buttonPress);

        SpinMotor(toggleData);

        ros::spinOnce();
        loop_rate.sleep();

    }

    return 0;
}