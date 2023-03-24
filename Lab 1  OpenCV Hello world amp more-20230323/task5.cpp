#include <opencv2/highgui.hpp>
#include <iostream>

int main(int argc, char** argv){

    //Create 256x256 image with one channel
    cv::Mat img1(256, 256, CV_8UC1);
    for(int i=0; i<img1.rows; i++){
        for(int j=0; j<img1.cols; j++){
            img1.at<uchar>(i, j)=i;          //vertical gradient on the first image
        }
    }

    cv::imshow("Vertical gradient", img1);
    cv::waitKey(0);

    //Create 256x256 image with one channel
    cv::Mat img2(256, 256, CV_8UC1);
    for(int i=0; i<img2.rows; i++){
        for(int j=0; j<img2.cols; j++){
            img2.at<uchar>(i, j)=j;          //horizontal gradient on the first image
        }
    }

    cv::imshow("Horizontal gradient", img2);
    cv::waitKey(0);

    //Create 300x300 chessboard with one channel
    cv::Mat img3(300, 300, CV_8UC1);
    for(int i=0; i<img3.rows; i++){
        for(int j=0; j<img3.cols; j++){
            if((i/20)%2==(j/20)%2){
                img3.at<uchar>(i, j)=255;
            }else{
                img3.at<uchar>(i, j)=0;
            }
        }
    }

    cv::imshow("Chessboard 20x20", img3);
    cv::waitKey(0);

    cv::Mat img4(300, 300, CV_8UC1);
    for (int i=0;i<img4.rows; i++){
        for(int j=0; j<img4.cols; j++){
            if((i/50)%2 == (j/50)%2){
                img4.at<uchar>(i, j)=255;
            }else{
                img4.at<uchar>(i, j)=0;
            }
        }
    }
    cv::imshow("Chessboard 50x50", img4);
    cv::waitKey(0);

    return 0;
}