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
    void myFunction(const std_msgs::Float32 &mssg);
};

void MyClass::myFunction(const std_msgs::Float32 &mssg)
{
    cout << mssg.data << endl;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "Listener");
    ros::NodeHandle n;
    ros::Rate loop_rate(100);

    
    
    std_msgs::Float32 value;
    MyClass myClass;

    ros::Subscriber variable = n.subscribe("Topic", 100, &MyClass::myFunction, &myClass);

        while(ros::ok()) //runs while ros is running
        {
            ros::spinOnce();
            loop_rate.sleep();
        
        }
        return 0;
}

