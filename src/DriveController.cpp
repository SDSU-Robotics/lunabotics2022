#include <string>
#include <unistd.h>

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <sensor_msgs/Joy.h>
#include "std_msgs/Bool.h"
#include "JoyMap.h"

using namespace std;

class Listener
{
public:
	void joyListener(const sensor_msgs::Joy::ConstPtr& Joy);
	void getJoyVals(bool buttons[], double axes[]) const;
	void toggle(const bool b, bool &current, bool &on, std_msgs::Bool &msg);


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

void Listener::toggle(const bool b, bool &current, bool &on, std_msgs::Bool &msg)
{
	bool prev;
	prev = current;
	current = b;

	if (prev && !current)
	{
		on = !on;
		ROS_INFO("RELEASED");
	}
		
	if (on)
	{
		ROS_INFO("ON");
		msg.data = true;

	}
	else
	{
		ROS_INFO("OFF");
		msg.data = false;
	}
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "DriveController");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	Listener listener;

	ros::Subscriber joySub = n.subscribe("joy", 100, &Listener::joyListener, &listener);
	
	bool buttons[12];
	double axes[6];

	bool Ybutton = buttons[JoyMap::MotorToggle];
	bool Ycurrent = 0; // initialized to false
	bool Yon = 0; // initialized to false

	// publishers
    ros::Publisher r_drive_pub = n.advertise<std_msgs::Float32>("ExcvRDrvPwr", 100);
	ros::Publisher l_drive_pub = n.advertise<std_msgs::Float32>("ExcvLDrvPwr", 100);
	ros::Publisher motor_toggle_pub = n.advertise<std_msgs::Bool>("MotorToggle", 100);
	
	// messages
    std_msgs::Float32 l_speed_msg;
    std_msgs::Float32 r_speed_msg;
	std_msgs::Bool motor_toggle_msg;
	
	while (ros::ok())
	{
        // initialize buttons and axes arrays
		listener.getJoyVals(buttons, axes);

		// get controller values
		float speed = axes[1]; // left Y
		float turn = 1 * axes[3]; // right X

		// get speed data
		l_speed_msg.data = 0.75 * speed + 0.4 * turn;
		r_speed_msg.data = 0.75 * speed - 0.4 * turn;
		// publish speed data
		l_drive_pub.publish(l_speed_msg);
		r_drive_pub.publish(r_speed_msg);

		// toggle Y button to turn motor on/off
		listener.toggle(Ybutton, Ycurrent, Yon, motor_toggle_msg);
		motor_toggle_pub.publish(motor_toggle_msg);
		
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}