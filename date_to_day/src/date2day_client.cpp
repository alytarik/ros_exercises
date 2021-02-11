#include "ros/ros.h"
#include "date_to_day/dateToDay.h"
#include <iostream>

int main(int argc, char** argv) {
    ros::init(argc, argv, "date_to_day_client");
    ros::NodeHandle n;
    int d, m, y;
    std::cout<<"Enter the day month year: ";
    std::cin>> d >> m >> y;
    ros::ServiceClient cli = n.serviceClient<date_to_day::dateToDay>("date_to_day");

    date_to_day::dateToDay service;
    service.request.day = d;
    service.request.month = m;
    service.request.year = y;

    if(cli.call(service)) {
        ROS_INFO("It's %s!", service.response.weekday.c_str());
    }

    else
        return 1;
    return 0;
}