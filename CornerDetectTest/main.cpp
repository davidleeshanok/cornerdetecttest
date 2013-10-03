//
//  main.cpp
//  CornerDetectTest
//
//  Created by David Lee-Shanok on 2013-10-02.
//  Copyright (c) 2013 David Lee-Shanok. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

using namespace std;
using namespace cv;

// Draw circles at feature point locations on an image
void drawOnImage(cv::Mat &image,
                 const std::vector<cv::Point> &points,
                 cv::Scalar color= cv::Scalar(255,255,255),
                 int radius=3, int thickness=2) {
    std::vector<cv::Point>::const_iterator it=
    points.begin();
    // for all corners
    while (it!=points.end()) {
        // draw a circle at each corner location
        cv::circle(image,*it,radius,color,thickness);
        ++it;
    }
}

int main(int argc, const char * argv[])
{
    //Test
    cv::Mat tableImage;
    cv::Mat unconvertedTableImage;
    cv::Mat channelTableImage;
    
    //Load image and convert
    unconvertedTableImage = imread("/Users/David/Desktop/pingpongtable.jpg");
    cout <<"Unconverted Image type: "; cout<< unconvertedTableImage.type() <<endl; //get image type
    
    unconvertedTableImage.convertTo(channelTableImage, CV_8U);
    cout <<"Channel Image type: "; cout<< channelTableImage.type() <<endl; //get image type after conversion to CV_8U
    
    cvtColor(channelTableImage, tableImage, CV_BGRA2GRAY);
    cout <<"Channel Image type: "; cout<< tableImage.type() <<endl; //get image type after channels changed
    
    //The image must have a type of CV_8UC1 or CV_32FC1 for cv::goodFeaturesToTrack to work, hence the conversion
    
    //Get edge points
    std::vector<cv::Point> pts;
    cv::goodFeaturesToTrack(tableImage, pts, 500, 0.01, 10);
    
    //Draw the points on the image
    drawOnImage(tableImage, pts);
    
    //Display image in window
    cv::namedWindow("Table Corners");
    cv::imshow("Table Corners", tableImage);
    
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}


