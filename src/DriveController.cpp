#include <string>
#include <unistd.h>

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <sensor_msgs/Joy.h>

using namespace std;

class Listener
{
public:
	void joyListener(const sensor_msgs::Joy::ConstPtr& Joy);
	void getJoyVals(bool buttons[], double axes[]) const;

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

int main (int argc, char **argv)
{
    ros::init(argc, argv, "DriveController");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

	Listener listener;

	ros::Subscriber joySub = n.subscribe("joy", 100, &Listener::joyListener, &listener);
	
	bool buttons[12];
	double axes[6];

	ros::Publisher l_drive = n.advertise<std_msgs::Float32>("ExcvLDrvCurrent", 100);
    ros::Publisher r_drive = n.advertise<std_msgs::Float32>("ExcvRDrvCurrent", 100);
	
    std_msgs::Float32 l_speed_msg;
    std_msgs::Float32 r_speed_msg;
	
	while (ros::ok())
	{
        listener.getJoyVals(buttons, axes);

		// get controller values
		float speed = axes[1]; // left Y
		float turn = 1 * axes[3]; // right X

		l_back_msg.data = 0.75 * speed + 0.4 * turn;
		r_back_msg.data = 0.75 * speed - 0.4 * turn;
		l_front_msg.data = 0.75 * speed + 0.4 * turn;
		r_back_msg.data = 0.75 * speed - 0.4 * turn;
		
		l_back_pub.publish(l_back_msg);
		r_back_pub.publish(r_back_msg);
		l_front_pub.publish(l_front_msg);
		r_front_pub.publish(r_front_msg);
		
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}