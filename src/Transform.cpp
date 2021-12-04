#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

void SetFootprint(){

}

int main(int argc, char** argv){
  ros::init(argc, argv, "footprint");
  ros::NodeHandle node;

  tf::TransformBroadcaster br;
  tf::Transform transform;

  ros::Rate rate(10.0);

    nav_msgs::Odometry quatOdom;

  while (node.ok()){
    transform.setOrigin( tf::Vector3(0.0, 0, -1) );
    transform.setRotation( tf::Quaternion(0, 0, 0, 1) );
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "base_footprint"));
    
    
    //transform.setOrigin( tf::Vector3(quatOdom.pose.pose.position.x, quatOdom.pose.pose.position.y, quatOdom.pose.pose.position.z));
    //transform.setRotation( tf::Quaternion(quatOdom.pose.pose.orientation.x, quatOdom.pose.pose.orientation.y, quatOdom.pose.pose.orientation.z, quatOdom.pose.pose.orientation.w) );

    //br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom_data_quat", "base_footprint"));
    
    rate.sleep();
  }
  return 0;
};