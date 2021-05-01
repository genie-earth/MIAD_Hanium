#include <stdio.h>
#include "ros/ros.h"
#include "std_msgs/Int32.h"

int main(int argc, char **argv)
{
	char str[100];
	
	ros::init(argc, argv,"name_of_pub_node");
	ros::NodeHandle nh;
	ros::Publisher i_am_the_publisher = nh.advertise<std_msgs::Int32>("name_of_topic", 100);

	ros::Rate loop_rate(5);

	while (ros::ok()){
		int num = 2;
		FILE *f = fopen("temp.txt", "r");
		fgets(str, sizeof(str), f);
		printf("%s\n", str);
		fclose(f);
		if(str[5] == 'f') num = 0;
		else if(str[5] == 'n') num = 1;
		else if(str[5] == 'e') num = 2;

		std_msgs::Int32 testmsg;
		testmsg.data = num;
		ROS_INFO("Value: %d\n", testmsg.data);

		i_am_the_publisher.publish(testmsg);

		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
