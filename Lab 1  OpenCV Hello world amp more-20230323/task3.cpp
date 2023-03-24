#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;

void checkColors(cv::Mat img){
    int width=img.cols;
    int height=img.rows;
    if(img.channels()==3){
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                img.at<cv::Vec3b>(i,j)[2]=0;                    //0 is yellow, 1 is red, 2 is blue
            }
        }
    }
}

int main(int argc, char** argv){
    int channels;
    int waitKey;
    if(argc<2){
        cout << "Image filename shall be provided!" << endl;
    }else{
        cv::Mat img=cv::imread(argv[1]);
        if(img.data==NULL){
            cout << "Imagine filename not correct!" << endl;
        }else{
            checkColors(img);
            channels=img.channels();                            //Gets number of channels
            cout << "Image channels: " << channels << endl;
            cv::namedWindow("Example 1");
            cv::imshow("Example 1", img);
            waitKey=cv::waitKey(0);
        }
    }
    cout << "waitKey value: " << waitKey << endl;               //Return waitKey value
    return 0;
}