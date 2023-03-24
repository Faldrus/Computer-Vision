#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    cv::Mat output;
    cv::Mat img=cv::imread(argv[1]);
    
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    
    cvtColor(img, output, cv::COLOR_RGB2GRAY);
    cv::imwrite("../image_grayscale.jpg", output);
    cv::imshow("Output", output);
    
    cv::waitKey(0);

    return 0;
}