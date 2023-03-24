#include <opencv2/highgui.hpp>
#include <iostream>

void maxFilter(cv:Mat image, int kernel){
    cv::Mat maxImage;
    
    if((kernel%2)==0){                 //kernel size is even
        cout << "Error!" << endl;
        return;
    }else{
        cv::erode(image, maxImage, kernel);
    }

}

void minFilter(cv:Mat image, int kernel){
    cv::Mat minImage;

    if((kernel%2)==0){
        cout << "Error!" << endl;
        return;
    }else{
        cv::dilate(image, minImage, kernel);
    }

}