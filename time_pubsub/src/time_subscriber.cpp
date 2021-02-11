#include "ros/ros.h"
#include "time_pubsub/myTime.h"

//Callback function is called when there is a new message and it prints the message.
void myCallback(const time_pubsub::myTimeConstPtr& msg){
    ROS_INFO("It's [%02d:%02d:%02d]!", msg->hour, msg->minute, msg->second);
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "time_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("currentTime", 100, myCallback);

    ros::spin();

    return 0;
}