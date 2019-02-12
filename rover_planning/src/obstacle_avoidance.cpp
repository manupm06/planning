#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "geometry_msgs/Twist.h"

bool distress=false;

void distanceCallback(const std_msgs::Int32 & dist_msg){
	if(dist_msg.data<10){
		distress=true;
	}
	else{
		distress=false;
	}
	return;
}
int main(int argc, char **argv)
{
	ros::init(argc, argv, "obst_avoid");

	ros::NodeHandle nh;

	ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
	ros::Subscriber dist_sub = nh.subscribe("distance", 1000, distanceCallback);

	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		geometry_msgs::Twist vel_msg;
		if(distress==false){
			vel_msg.linear.x=1;
		}
		else{
			vel_msg.angular.z=1;
		}

		vel_pub.publish(vel_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}		
