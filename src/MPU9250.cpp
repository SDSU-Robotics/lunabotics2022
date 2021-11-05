#include "Wire.h"
#include "libraries/firmware/I2Cdev/I2Cdev.h"
#include "libraries/firmware/MPU6050/MPU6050_6Axis_MotionApps20.h"

// creating an MPU6050 handle which can be used for MPU9250
MPU6050 mpu;

#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <tf/transform_broadcaster.h>

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;
ros::NodehHandle n;
geometry_msgs::Vector3 orient;
ros::Publisher impu_pub("imu_data", &orient);

// the frame_id helps to visualize the Tranform data of IMU w.r.t. this link
char frameid[] = "/base_link";
char child[] = "/imu_frame";

// defining an LED pin to show te status of IMU data read
#define LED_PIN 13
bool blinkState = false;

// MPU control/motion vars
Quaternion q;           // [w,x,y,z]
VectorFloat gravity;    // [x,y,z]
float ypr[3];           // [yaw,pitch,roll]

volatile bool mpuInterrupt = false;
void dmpDataReady()
{
  mpuInterrupt = true;
}

void setup()
{
    Wire.begin();

    n.initNode();
    broadcaster.init(n);
    n.advertise(imu_pub);
    mpu.initialize();
    
    devStatus = mpu.dmpInitialize();
    if(devStatus == 0)
    {
        mpu.setDMPEnabled(true);
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    }

    // configure LED pin
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    if (!dmpReady) return;

    while (!mpuInterrupt && fifoCount < packetSize)
    { ; } // literally do nothing and wait

    // reset interrupt flag and gat INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus - mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    if ((mpuIntStatus & 0x10) || fifoCount == 1024)
    {
        // reset for clean continue
        mpu.resetFIFO();
    } // otherwise, check for DMP data ready interrupt 
    else if (mpuIntStatus & 0x01)
    {
        // wait for correct available data length
        while (fifoCount < packetSize)
          fifoCount = mpu.getFIFOCount();

        mpu.getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;

        // display quaternion values
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dempGetYawPitchRoll(ypr, &q, &gravity);

        orient.x = ypr[0] * 180 / M_PI;
        orient.y = ypr[1] * 180 / M_PI;
        orient.z = ypr[2] * 180 / M_PI;
        imu_pub.publish(&orient);

        // assigning values to TF header and publish the transform
        t.header.frame_id = frameid;
        t.child_frame_id = child;
        t.transform.translation.x = 1.0;
        t.transform.rotation.x = q.x;
        t.transform.rotation.y = q.y;
        t.transform.rotation.z = q.z;
        t.transform.rotation.w = q.w;
        t.header.stamp = n.now();
        broadcaster.sendTransform(t);

        n.spinOnce();

        delay(200); // delay 200 ms

        // blink LED
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
        delay(200);    
    }
}
