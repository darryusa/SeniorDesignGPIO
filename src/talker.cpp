#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main (int argc, char **argv)
{

	ros::init(argc, argv, "talker");

	ros::NodeHandle n;

	// tells master we are publishing a String message on the topic chatter
	// if published too quickly we will buffer a max of 100 messages before
	// beginning to throw away old ones
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 100);

	// publish at the rate of one message per second (aka 1HZ)
	ros::Rate loop_rate(0.1);

	int count = 0;
	while (ros::ok())
	{
	 	std_msgs::String msg;
		
		std::stringstream ss;
		
		if(count <= 3)
		{				
		ss << "ball " ; 
		}
		else if(count == 4)
		{
		ss << "off " ; 
		}
		else if(count >= 5 && count < 7)
		{
		ss << "launcher " ; 
		}
		else 
		{
		ss << "off " ; 
		}

		msg.data = ss.str();
		
		// publishing string message to anyone who is connected to chatter topic
		chatter_pub.publish(msg);

		ROS_INFO("%s", msg.data.c_str());

		// necessary if receiving any callbacks
		ros::spinOnce();

		// use ros::Rate object to sleep for the time remaining to let us hit our 
		// publish rate of 1HZ
		loop_rate.sleep();
		++count;
	}

	return 0;
}


