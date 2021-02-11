#include "ros/ros.h"
#include <time.h> 
#include "time_pubsub/myTime.h"     //include our custom message type "myTime"

int main(int argc, char** argv) {
    ros::init(argc, argv, "time_publisher");
    ros::NodeHandle n;

    //Create a publisher with topic "currentTime" that broadcasts current time as a "myTime" message.
    ros::Publisher pub = n.advertise<time_pubsub::myTime>("currentTime",100);

    //Publish the time every second
    ros::Rate loop_rate(1);

    while(ros::ok()) {
        time_pubsub::myTime msg;

        //Get the system time and assign to message
        auto t = time(0);
        msg.second = localtime(&t)->tm_sec;
        msg.minute = localtime(&t)->tm_min;
        msg.hour = localtime(&t)->tm_hour;

        pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}