#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "ImgWindow";

#define BALL_HUE 110

class ImageProcessor {
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber sub_;
    image_transport::Publisher pub_;


    public:
    ImageProcessor() : it_(nh_) {
        sub_ = it_.subscribe("image", 1, &ImageProcessor::imageCallback, this);
        pub_ = it_.advertise("/image_converter/output_video", 1);

        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageProcessor() {
        cv::destroyWindow(OPENCV_WINDOW);
    }

    void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
        cv_bridge::CvImagePtr ptr;
        ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

        cv::Mat hsv, filtered;
        cv::Mat contour_image(ptr->image.rows, ptr->image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::cvtColor(ptr->image, hsv, cv::COLOR_BGR2HSV);

        cv::inRange(hsv, cv::Scalar(BALL_HUE-20, 60, 60), cv::Scalar(BALL_HUE + 20, 255, 255), filtered);
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(filtered, contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

        for(int i=0;i<contours.size();i++)
        {
            double contArea = cv::contourArea(contours[i]);
            if(contArea>100) {
                drawContours(ptr->image, contours, i, cv::Scalar(255,0,0), 1);
                auto M = cv::moments(contours[i]);
                auto cX = int(M.m10 / M.m00);
                auto cY = int(M.m01 / M.m00);
                float radius;
                cv::Point2f center;
                cv::minEnclosingCircle( contours[i], center, radius);
                cv::circle(ptr->image,cv::Point(cX, cY),radius,cv::Scalar(0,0,255));
            }

        }

        cv::imshow(OPENCV_WINDOW, ptr->image);
        cv::waitKey(3);

        pub_.publish(ptr->toImageMsg());
    }
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "image_converter");
    ImageProcessor ic;
    ros::spin();
    return 0;
}

