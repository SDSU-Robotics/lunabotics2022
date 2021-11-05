#include <string>
#include <unistd.h>
#include <iostream>
#include "std_msgs/Bool.h"
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <thread>
#include <time.h>
#include <conio.h>

using namespace std;

int main(int argc, char**argv)
{
    int status = 0;
    srand(time(0));
    float Atime, Btime, Ctime, Dtime, Etime;

    ros::init(argc, argv, "testNode");
	  ros::NodeHandle n;
	  ros::Rate loop_rate(100);

    while (ros::ok())
    {
        switch(status)
        {
           case 0:
           Atime = clock();
            for (status; status == 0;)
             {
              cout << "Navigation towards site" << endl;
              if((clock() - Atime) / CLOCKS_PER_SEC >= 5)
               {
               status++;
               cout << " " << status << endl;
               }
             }
             break;
           case 1:
           Btime = clock();
            for(status; status == 1;)
             {
              cout << "Excavation at site" << endl;
              if((clock() - Btime) / CLOCKS_PER_SEC >= 5)
              {
               status++;
               cout << " " << status << endl;
              }
             }
             break;
           case 2:
           Ctime = clock();
            for (status; status == 2;)
             {
              cout << "Transfer material" << endl;
              if((clock() - Ctime) / CLOCKS_PER_SEC >= 5)
              {
              status++;
              cout << " " << status << endl;
              }
             }
             break;
           case 3:
           Dtime = clock();
            for(status; status == 3;)
             {
              cout << "Navigate back home" << endl;
              if((clock() - Dtime) / CLOCKS_PER_SEC >= 5)
              {
              status++;
              cout << " " << status << endl;
              }
             }
             break;
           case 4:
           Etime = clock();
            cout << "if you love me let me goo" << endl;
             for (status; status == 4;)
             {
                cout << "Die" << endl;
                if((clock() - Etime) / CLOCKS_PER_SEC >= 5)
                {
                status -= 4;
                cout << " " << status << endl;
                }
             }
             break;
        }
    }

    return 0;
}