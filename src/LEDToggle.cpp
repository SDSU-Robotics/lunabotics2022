#include "ros/ros.h"
#include "iostream"

#include <sensor_msgs/Joy.h>
#include "JoyMap.h"

#include "std_msgs/Bool.h"

using namespace std;

bool buttons[12] = { 0 };
double axes[6] = { 0 };

void JoyListener(const sensor_msgs::Joy::ConstPtr& Joy)
{
    for (int i = 0 ; i < 12; i++)   
        buttons[i] = Joy->buttons[i];
    
    for (int i = 0 ; i < 12; i++)
        axes[i] = Joy->axes[i];

}

bool Toggle(const bool b, bool &current, bool &on)
{
    bool toggleData;
    bool prev = current;
    current = b;

    if (prev && !current)
        on = !on;

    if (on)
        toggleData = true;

    else
        toggleData = false;

    return toggleData;

}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "LEDToggle");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    ros::Subscriber joySub = n.subscribe("joy", 100, JoyListener);

    int toggleButton = {JoyMap::toggle};
    bool buttonCurrent = false;
    bool buttonPress = false;

    std_msgs::Bool ledToggleData;
    ros::Publisher ledTogglePub = n.advertise<std_msgs::Bool>("LEDToggle", 100);

    while(ros::ok())
    {
        ledToggleData.data = Toggle(buttons[toggleButton], buttonCurrent, buttonPress);
        ledTogglePub.publish(ledToggleData);

        ros::spinOnce();
        loop_rate.sleep();
    
    }

    return 0;
}