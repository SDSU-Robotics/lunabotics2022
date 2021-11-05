#include <string>
#include <unistd.h>
#include <iostream>
#include "std_msgs/Bool.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"

using namespace std;

class Listener
{
    public:
    void myFn(const std_msgs::Float32 crack);
};


void fn(const std_msgs::Float32 crack)
{
    cout << crack.data << endl;
}

void Listener::myFn(const std_msgs::Float32 crack)
{
    cout << crack.data << endl;
}

int main(int argc, char**argv)
{
    Listener listener;
    
    ros::init(argc, argv, "HIV");
        ros::NodeHandle n;
        ros::Rate loop_rate(69);

        ros::Subscriber EatPath = n.subscribe("topic", 69, &Listener::myFn, &listener);
    
    while(ros::ok())
    {
         ros::spinOnce();
        loop_rate.sleep();

    }
    return 0;
}