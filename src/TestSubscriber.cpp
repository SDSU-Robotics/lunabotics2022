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
  void myPain(const std_msgs::Float32 butt);
};

void Listener::myPain(const std_msgs::Float32 butt)
{
 cout << butt.data << endl;
}

void Pain(const std_msgs::Float32 butt)
{
 cout << butt.data << endl;
}

int main(int argc, char**argv)
{
 ros::init(argc, argv, "Nodetest");
 ros::NodeHandle n;
 ros::Rate loop_rate(100);

 Listener listener;

 //ros::Subscriber TestofNodes = n.subscriber ("Testtopic", 420, Pain);
 ros::Subscriber TestofNodes = n.subscribe("Testtopic", 420, &Listener::myPain, &listener);

 while (ros::ok())
 {
  ros::spinOnce();
  loop_rate.sleep();
 }

 return 0;
}