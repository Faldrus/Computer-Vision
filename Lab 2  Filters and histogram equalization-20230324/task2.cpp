/*
  The best options to remove the cables were:
    -max filter -> kernel = 5
    -min filter -> kernel = NA, the cables never really disappear
*/
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "functions.h"

using namespace std;

int main(int argc, char** argv){
    cv::Mat img=cv::imread(argv[1]);
    
    if(img.data==NULL){
        std::cout << "Image not found" << std::endl;
        return -1;
    }

    cv::namedWindow("Gray scale");
    cv::imshow("Gray scale", img);
    cv::waitKey(0);

    cv::Mat grayscale_img(img.rows, img.cols, CV_8U);
    cv::cvtColor(img, grayscale_img, cv::COLOR_BGR2GRAY, 0);

    for(int kernel_size=1; kernel_size<35; kernel_size+=2){
        std::cout << "Starting with kernel " << kernel_size << std::endl;
        cv::Mat min_img=min_filter(grayscale_img, kernel_size);
        cv::Mat max_img=max_filter(grayscale_img, kernel_size);

        char min_filename[50];
        sprintf(min_filename, "./filtered/min_filtered_kernel_%d.jpg", kernel_size);
        cv::imwrite(min_filename, min_img);

        char max_filename[50];
        sprintf(max_filename, "./filtered/max_filtered_kernel_%d.jpg", kernel_size);
        cv::imwrite(max_filename, max_img);

    }

    return 0;
}