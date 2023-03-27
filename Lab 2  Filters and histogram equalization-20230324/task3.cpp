/*
  The best options to remove the cables were:
    -max filter -> kernel = 5
    -min filter -> kernel = NA, the cables never really disappear
*/

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "functions.h"
#include <opencv2/highgui.hpp>
#include <iostream>

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
        sprintf(min_filename, "./filtered/min_filter_%d.jpg", kernel_size);
        cv::imwrite(min_filename, min_img);

        char max_filename[50];
        sprintf(max_filename, "./filtered/max_filter_%d.jpg", kernel_size);
        cv::imwrite(max_filename, max_img);

        cv::Mat median_filtered(grayscale_img.rows, grayscale_img.cols, CV_8U);
        cv::medianBlur(grayscale_img, median_filtered, kernel_size);
        char median_filename[50];
        sprintf(median_filename, "./filtered/median_filter_%d.jpg", kernel_size);
        cv::imwrite(median_filename, median_filtered);

        cv::Mat gaussian_filtered(grayscale_img.rows, grayscale_img.cols, CV_8U);
        cv::GaussianBlur(grayscale_img, gaussian_filtered, cv::Size(kernel_size, kernel_size), 0, 0, cv::BORDER_DEFAULT);
        char gaussian_filename[50];
        sprintf(gaussian_filename, "./filtered/gaussian_filter_%d.jpg", kernel_size);
        cv::imwrite(gaussian_filename, gaussian_filtered);
    }

    return 0;
}