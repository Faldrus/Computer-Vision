#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, char** argv){
    //Check if the filename is provided
    if(argc<2){
        cout << "Image filename shall be provided!" << endl;
    }else{
        cv::Mat img=cv::imread(argv[1]);
        //Check if image provided is valid(imread returns null if image is wrong)
        if(img.data==NULL){
            cout << "Imagine filename not correct!" << endl;
        }else{
            cv::namedWindow("Example 1");
            cv::imshow("Example 1", img);
            cv::waitKey(0);
        }
    }
    return 0;
}