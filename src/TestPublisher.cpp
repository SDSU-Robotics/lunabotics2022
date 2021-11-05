#include <string>
#include <unistd.h>
#include <iostream>
#include "std_msgs/Bool.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"

using namespace std;

int main(int argc, char**argv)
{

 ros::init(argc, argv, "testNode");
	ros::NodeHandle n;
	ros::Rate loop_rate(100);

    ros::Publisher Testpub = n.advertise<std_msgs::Float32>("Testtopic", 100);

    std_msgs::Float32 test;
    test.data = 1;

    while(ros::ok())
    {
        Testpub.publish(test);

        ros::spinOnce();
		loop_rate.sleep();
    }

return 0;
}