#include "ros/ros.h"
#include "iostream"

#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include "ctre/phoenix/motorcontrol/SensorCollection.h"
#include "DeviceIDs.h"

using namespace std;

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

TalonSRX motor = {DeviceIDs::motor};

// check if func needs to be before or after int main
// then adjust accordingly in the doc





int main (int argc, char **argv)
{
    ros::init(argc, argv, "motorspin");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    phoenix::platform::can::SetCANInterface("can0");

    while(ros::ok())
    {
        SpinMotor();

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;

}

void SpinMotor ()
{
    motor.Set(ControlMode::PercentOutput, 1);

    ctre::phoenix::unmanaged::FeedEnable(100);

}
