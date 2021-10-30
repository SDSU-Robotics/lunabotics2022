#include <string>
#include <unistd.h>

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <sensor_msgs/Joy.h>
#include "std_msgs/Bool.h"
#include "JoyMap.h"

using namespace std;

#define DRIVE_SCALE 1

class Listener
{
public:
	void joyListener(const sensor_msgs::Joy::ConstPtr& Joy);
	void getJoyVals(bool buttons[], double axes[]) const;
	void F32Toggle(const bool b, bool &current, bool &on, std_msgs::Float32 &msg); // Float32 message

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

void Listener::F32Toggle(const bool b, bool &current, bool &on, std_msgs::Float32 &msg)
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
    ros::init(argc, argv, "ManualDriveController");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	Listener listener;

	ros::Subscriber joySub = n.subscribe("Excv/joy", 100, &Listener::joyListener, &listener);
	
	bool buttons[12];
	double axes[6];

	uint auger = {JoyMap::AugerToggle};
	bool augerCurrent = false; // initialized to false
	bool augerOn = false; // initialized to false

	uint linAct = {JoyMap::LinActToggle};
	bool linActCurrent = false; // initialized to false
	bool linActOn = false; // initialized to false

	int Lstick_Yaxis = {JoyMap::LeftDrive};
    int Rstick_Yaxis = {JoyMap::RightDrive};

	// publishers
    ros::Publisher r_drive_pub = n.advertise<std_msgs::Float32>("RDrvPwr", 100);
	ros::Publisher l_drive_pub = n.advertise<std_msgs::Float32>("LDrvPwr", 100);
	ros::Publisher auger_toggle_pub = n.advertise<std_msgs::Float32>("AugerToggle", 100);
	ros::Publisher lin_act_toggle_pub = n.advertise<std_msgs::Float32>("LinActToggle", 100);
	
	// messages
    std_msgs::Float32 l_speed_msg;
    std_msgs::Float32 r_speed_msg;
	std_msgs::Float32 auger_toggle_msg;
	std_msgs::Float32 lin_act_toggle_msg;
	
	while (ros::ok())
	{
        // initialize buttons and axes arrays
		listener.getJoyVals(buttons, axes);

		// get controller values
		float speed = axes[1]; // left Y
		float turn = 1 * axes[3]; // right X

		// get speed data
		l_speed_msg.data = axes[Lstick_Yaxis] * DRIVE_SCALE; // left up/down stick
		r_speed_msg.data = axes[Rstick_Yaxis] * DRIVE_SCALE; // right up/down stick
		// publish speed data
		l_drive_pub.publish(l_speed_msg);
		r_drive_pub.publish(r_speed_msg);

		// toggle Y button to turn auger motor on/off
		listener.F32Toggle(buttons[auger], augerCurrent, augerOn, auger_toggle_msg);
		auger_toggle_pub.publish(auger_toggle_msg);

		// toggle A button to toggle linear actuator
		listener.F32Toggle(buttons[linAct], linActCurrent, linActOn, lin_act_toggle_msg);
		lin_act_toggle_pub.publish(lin_act_toggle_msg);
		
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}