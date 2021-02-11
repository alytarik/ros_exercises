#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

void scanCallback(sensor_msgs::LaserScan msg) {
    float min = std::numeric_limits<float>::max(), max = 0;


    for (int i = 0; i < msg.ranges.size(); i++)
    {
        if(!isnan(msg.ranges[i])) {
            if(msg.ranges[i] < min)
                min = msg.ranges[i];

            else if(msg.ranges[i] > max)
                max = msg.ranges[i];
        }
    }
    
    ROS_INFO("Min range: %f", min);
    ROS_INFO("Max range: %f", max);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "lidar_subscriber");
    ros::NodeHandle n;
    ros::Subscriber scan_sub = n.subscribe("/scan", 100, scanCallback);
    ros::spin();
}