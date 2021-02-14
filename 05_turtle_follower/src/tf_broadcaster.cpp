#include "ros/ros.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/TransformStamped.h"
#include "turtlesim/Pose.h"
#include "boost/bind.hpp"

void poseCallback(const turtlesim::PoseConstPtr& msg, std::string turtle_name) {
    tf2_ros::TransformBroadcaster bc;
    geometry_msgs::TransformStamped transformStamped;


    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "world";
    transformStamped.child_frame_id = turtle_name + "_frame";

    transformStamped.transform.translation.x = msg->x;
    transformStamped.transform.translation.y = msg->y;
    transformStamped.transform.translation.z = 0.0;

    tf2::Quaternion rot;
    rot.setEuler(0, 0, msg->theta);
    transformStamped.transform.rotation.x = rot.x();
    transformStamped.transform.rotation.y = rot.y();
    transformStamped.transform.rotation.z = rot.z();
    transformStamped.transform.rotation.w = rot.w();
    
    bc.sendTransform(transformStamped);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "turtle_tf_broadcaster");
    ros::NodeHandle n("~");
    std::string turtle_name;
    n.getParam("turtle", turtle_name);
    std::string topic_name = "/" + turtle_name + "/pose";
    ros::Subscriber sub = n.subscribe<turtlesim::Pose>(topic_name, 10, boost::bind(poseCallback, _1, turtle_name));
    ros::spin();
}