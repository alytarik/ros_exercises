#include "ros/ros.h"
#include "date_to_day/dateToDay.h"
#include <chrono>

bool dateToDay(date_to_day::dateToDay::Request& req, date_to_day::dateToDay::Response& res) {
    std::string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    //Create a time object with given arguments, then get the weekday index.
    std::tm time_in = {0, 0, 0, req.day, req.month, req.year - 1900};
    std::time_t time_temp = std::mktime(&time_in);
    const std::tm * time_out = std::localtime(&time_temp);

    //Find the name of the day from days[] array.
    res.weekday = days[time_out->tm_wday];

    return true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "date_to_day_server");
    ros::NodeHandle n;
    ros::ServiceServer server = n.advertiseService("date_to_day", dateToDay);
    ros::spin();
    return 0;
}