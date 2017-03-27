// exampleApp.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "gpio_test/jetsonGPIO.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
 
using namespace std;

char ball[5] = "ball";
char nobjt[4] = "off";
char launch[9] = "launcher";

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{	
	jetsonTX1GPIONumber C = gpio219;
	jetsonTX1GPIONumber D = gpio186;

	gpioExport(C);
	gpioExport(D);
	gpioSetDirection(C, outputPin);
	gpioSetDirection(D, outputPin);

 	ROS_INFO("I heard: [%s]", msg->data.c_str());
	
	// if ball found by camera
	if(strcmp(ball, msg->data.c_str()) == 0) 
	{
		gpioSetValue(C, on);
		gpioSetValue(D, off);
	}
	// if no ball or launcher found by camera
	else if(strcmp(nobjt, msg->data.c_str()) == 0)
	{
		gpioSetValue(C, off);
		gpioSetValue(D, off);
	}
	// if launcher found by camera
	else if(strcmp(launch, msg->data.c_str())  == 0)
	{
		gpioSetValue(C, off);
		gpioSetValue(D, on);
	}
	// redundent, will not need second comparison once camera sending messages
	else
	{
		gpioSetValue(C, off);
		gpioSetValue(D, off);
	}
	
}


int main(int argc, char *argv[])
{
//   	jetsonTX1GPIONumber C = gpio219 ;     // Output
//     	jetsonTX1GPIONumber D = gpio186 ;     // Output
	jetsonTX1GPIONumber En = gpio187 ;     // Enable, always high
	
	gpioExport(En);
	gpioSetDirection(En, outputPin);
	gpioSetValue(En, on);
	
//	for(int i=0; i<8; i++)
//	{
	
//		gpioSetValue(C, on);
//		usleep(200000);
//	}
//	gpioSetValue(C, off);    

	ros::init(argc, argv, "exampleGPIOApp");

 	ros::NodeHandle n;
	 
  	ros::Subscriber sub = n.subscribe("chatter", 100, chatterCallback);

	ros::spin();

    // Enable set to high
//    gpioSetValue(En, on);

    
    
    
     // Flash the LED 5 times
   /* for(int i=0; i<8; i++)
    {
   
        gpioSetValue(C, on);
        usleep(200000);         // on for 200ms
       
      //  gpioSetValue(C, off);
      //  usleep(200000);         // off for 200ms
    }
 
	gpioSetValue(C, off);    
    */
 
   /* if(option == 108)
    {
    
    for(int i=0; i<8; i++)
    {
     	gpioSetValue(C, on);
        usleep(200000);

	gpioSetValue(C, off);
        usleep(200000);
     }
  
     }*/

  //  gpioSetValue(C, off);

    gpioSetValue(En, off);
    return 0;
}


