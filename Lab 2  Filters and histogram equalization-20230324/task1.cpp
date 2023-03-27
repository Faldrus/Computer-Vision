#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    cv::Mat img=cv::imread(argv[1]);
    
    if(img.data==NULL){
        cout << "Image not found" << endl;
        return -1;
    }

    cv::namedWindow("Gray scale");
    //Show colored image
    cv::imshow("Gray scale", img);
    cv::waitKey(0);

    //Convert to grayscale
    cv::Mat gray_scale_img(img.rows, img.cols, CV_8U);
    cvtColor(img, gray_scale_img, cv::COLOR_RGB2GRAY);
    
    //Show grayscale image
    cv::imshow("Gray scale", gray_scale_img);
    cv::waitKey(0);
    
    return 0;

}