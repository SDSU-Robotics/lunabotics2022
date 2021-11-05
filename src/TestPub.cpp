#include <string>
#include <unistd.h>
#include <iostream>
#include "std_msgs/Bool.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"

using namespace std;

int main(int argc, char**argv)
{
    ros::init(argc, argv, "AIDS");
        ros::NodeHandle n;
        ros::Rate loop_rate(69);

        ros::Publisher Testpath = n.advertise<std_msgs::Float32>("topic", 69);

        std_msgs::Float32 bean;

        bean.data = 69;


    while(ros::ok())
    {
        Testpath.publish(bean);
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}