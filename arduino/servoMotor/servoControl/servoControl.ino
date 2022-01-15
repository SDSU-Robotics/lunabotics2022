#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
 #else
  #include <WProgram.h>
 #endif

 #include <Servo.h>
 #include <ros.h>
 #include <std_msgs/UInt16.h>
 

 ros::NodeHandle  nh;

 Servo servo;

 void servo_cb( const std_msgs::UInt16& cmd_msg){
  servo.write(smd_msg.data);
  digitalWrite(13, HIGH-digitalRead(13));
  
 }

 ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

 void setup(){
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);

  servo.attach(9);
 }

 void loop(){
  nh.spinOnce();
  delay(1);
 }
