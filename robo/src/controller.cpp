#include <ros/ros.h>
#include <stdio.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>


geometry_msgs::Twist vel;
sensor_msgs::LaserScan laser;
ros::Publisher pub;

float robot_x =0.0;
float robot_y =0.0;


void odomCallback(const nav_msgs::OdometryConstPtr & msg)
{


	robot_x = msg->pose.pose.position.x;
	robot_y = msg->pose.pose.position.y;
	
}


void laserCallback(const sensor_msgs::LaserScanConstPtr & msg)
{
	int size = int((-msg->angle_min+msg->angle_max)/msg->angle_increment);
	float x_[size];
	float y_[size];
	float distance=0.0;
	float distance_max=0.0;
	int max_dist_point=0;
	int point_index =0;
        geometry_msgs::Twist vel;
	for ( int i =0; i < size; i++)
	{	
		if ((msg->ranges[i] > msg->range_min) && (msg->ranges[i]<75.0))
			{ 
			x_[point_index]=(msg->ranges[i]*cos(msg->angle_min+(i*msg->angle_increment)));
			y_[point_index]=(msg->ranges[i]*sin(msg->angle_min+(i*msg->angle_increment)));
			point_index++;		
			}

	} 	
	for ( int j =0; j <point_index; j++)
	{	
		distance = (sqrt(pow((x_[0] - x_[j]),2)+pow((y_[0] - y_[j]),2)));
		if (distance > distance_max)
		{
			max_dist_point= j;
			distance_max = distance;
		}
	}

	vel.linear.y= ((((y_[0]+y_[max_dist_point])/2)+robot_y)-robot_y);
	vel.linear.x= ((((x_[0]+x_[max_dist_point])/2)+robot_x)-robot_x)/10;
	pub.publish(vel);
}


int main (int argc, char** argv)
{
  
    ros::init(argc,argv,"controller");
    ros::NodeHandle nh;
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    ros::Subscriber odom_pub=nh.subscribe<nav_msgs::Odometry>("/odom",1,odomCallback);
    ros::Subscriber laser_pub=nh.subscribe<sensor_msgs::LaserScan>("/scan",1,laserCallback);
    ros::Rate loop_rate(100);
    sleep(5);
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
}
