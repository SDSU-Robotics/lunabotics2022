#include <string>
#include <unistd.h>

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <sensor_msgs/Joy.h>
#include "std_msgs/Bool.h"
//#include "JoyMap.h"

using namespace std;

class Listener
{
public:
	void joyListener(const sensor_msgs::Joy::ConstPtr& Joy);
    void Listener::augerToggle(const bool b, bool &current, bool &on, std_msgs::Float32 &msg)

private:
    bool _buttons[12] = { 0 };
	double _axes[6] = { 0 };
	
};

void Listener::joyListener(const sensor_msgs::Joy::ConstPtr& Joy)
{
	for (int i = 0 ; i < 12; i++)
		_buttons[i] = Joy->buttons[i];

    for (int i = 0; i < 6; i++)
        _axes[i] = Joy->axes[i];
}

void Listener::getJoyVals(bool buttons[], double axes[]) const
{
    for (int i = 0; i < 12; i++)
        buttons[i] = _buttons[i];

    for (int i = 0; i < 6; i++)
        axes[i] = _axes[i];
}

void Listener::augerToggle(const bool b, bool &current, bool &on, std_msgs::Float32 &msg)
{
	bool prev = current;
	current = b;

	if (prev && !current)
	{
		on = !on;
		ROS_INFO("PRESSED");
	}
		
	if (on)
	{
		ROS_INFO("ON");
		msg.data = 1;

	}
	else
	{
		ROS_INFO("OFF");
		msg.data = 0;
	}
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

    bool buttons[12];
	double axes[6];

    int Ybutton = {JoyMap::AugerToggle};
	bool Ycurrent = false; // initialized to false
	bool Yon = false; // initialized to false

    Listener listener

    ros::Subscriber joySub = n.subscribe("Excv/joy", 100, &Listener::joyListener, &listener);

    std_msgs::Float32 motor_toggle_msg;

	ros::Publisher motor_toggle_pub = n.advertise<std_msgs::Float32>("AugerToggle", 100);
	
    while (ros::ok())
	{
        /*listener.getJoyVals(buttons, axes);

        listener.augerToggle(buttons[Ybutton], Ycurrent, Yon, motor_toggle_msg);
		motor_toggle_pub.publish(motor_toggle_msg);
		*/
        ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}