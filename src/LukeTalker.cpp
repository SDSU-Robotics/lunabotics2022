#include <string>
#include <unistd.h>
#include <iostream>
#include "std_msgs/Bool.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"


using namespace std;

class MyClass
{
    public:
      void myFunction(std_msgs::Float32 &mssg);
};

void MyClass::myFunction(std_msgs::Float32 &mssg)
{
    mssg.data = 1.5;
}

int main (int argc, char **argv)
{
    ros::init(argc, argv, "Talker");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);
    
    MyClass myClass;

    ros::Publisher variable = n.advertise<std_msgs::Float32>("Topic", 100);

    
    std_msgs::Float32 value;

        while (ros::ok()) // runs while ros is running
        {
            myClass.myFunction(value);

            variable.publish(value);
            ROS_INFO("%f", value.data);

            ros::spinOnce();
            loop_rate.sleep();

        }
    return 0;
}