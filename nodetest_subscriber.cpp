#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define OUT1 12      //BCN_GPIO 10
#define OUT2 13      //BCM_GPIO 9
#define OUT3 4       //BCM_GPIO 23
#define OUT4 5       //BCM_GPIO 24

typedef struct arg_t{
	int delay;
	int num_step;
}myarg;


void setsteps(int w1, int w2, int w3, int w4)
    {
         pinMode(OUT1,OUTPUT);
         digitalWrite(OUT1,w1);
         pinMode(OUT2,OUTPUT);
         digitalWrite(OUT2,w2);
         pinMode(OUT3,OUTPUT);
         digitalWrite(OUT3,w3);
         pinMode(OUT4,OUTPUT);
         digitalWrite(OUT4,w4);
     }

void MaskOn(int del, int steps)
{	
	int i;
	for(i=0;i<=steps;i++)
        {
                  setsteps(1,0,0,1);
                   delay(del);
                   setsteps(0,0,1,1);
                   delay(del);
                   setsteps(0,1,1,0);
                   delay(del);
                   setsteps(1,1,0,0);
                   delay(del);
        }
	delay(3000);
        for(i=0;i<=steps;i++)
        {
                  setsteps(1,1,0,0);
                  delay(del);
                  setsteps(0,1,1,0);
                  delay(del);
                  setsteps(0,0,1,1);
                  delay(del);
                  setsteps(1,0,0,1);
                  delay(del);
        }
	delay(500);
	
}
void *wearMask (void *arg)
{	
	int del,steps;  
	myarg *args = (myarg*)arg;
	del = args->delay;
	steps = args->num_step;	
        int i;
        for(i=0;i<=steps;i++)
        {
                  setsteps(1,1,0,0);
                  delay(del);
                  setsteps(0,1,1,0);
                  delay(del);
                  setsteps(0,0,1,1);
                  delay(del);
                  setsteps(1,0,0,1);
                  delay(del);
        }
	delay(5000);
	for(i=0;i<=steps;i++)
        {
                  setsteps(1,0,0,1);
                   delay(del);
                   setsteps(0,0,1,1);
                   delay(del);
                   setsteps(0,1,1,0);
                   delay(del);
                   setsteps(1,1,0,0);
                   delay(del);
        }
}

void backward (int del,int steps)
      {
           int k;
           for(k=0;k<=steps;k++)
           {
                   setsteps(1,0,0,1);
                   delay(del);
                   setsteps(0,0,1,1);
                   delay(del);
                   setsteps(0,1,1,0);
                   delay(del);
                   setsteps(1,1,0,0);
                   delay(del);
           }
      }

//void *printString (void *args)
//{
//	printf("Hello, world!\n");
//}


void subscriberCallback(const std_msgs::Int32 msg){
	ROS_INFO("Received: %d\n", msg.data);
	if(msg.data == 1)
	MaskOn(2,500);
	else if(msg.data==0)
	system("omxplayer -o local /home/bitdol/MaskWear.wav");
	//else if(msg.data ==2)
	//system("omxplayer -o local /home/bitdol/pi_recodingd.wav");
}



int main(int argc, char **argv){
	ros::init(argc, argv,"name_of_sub_node");
	ros::NodeHandle nh;
	ros::Subscriber i_am_the_subsrciber = nh.subscribe("name_of_topic",10, subscriberCallback);
	//ros::Rate rate(5);

	//pthread_t p_thread1;
	
/*
	int pid1;
	pid1 = pthread_create(&p_thread1, NULL, printString, NULL);
	if(pid1<0)
	{
		perror("thread creation error");
		exit(1);
	}
*/
	//pthread_t forward_th;
	
	/*int pid2;

	myarg arg_s;
	arg_s.delay = 5;
	arg_s.num_step = 128;
	pid2 = pthread_create(&forward_th, NULL, wearMask, &arg_s);
	if(pid2<0)
	{
		perror("thread creation error");
		exit(1);
	}
	*/
	if(wiringPiSetup() == -1)
    	return 1;

	ros::spin();
	
	return 0;
}
