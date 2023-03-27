#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, char** argv){
    //Check if the filename is provided
    if(argc<2){
        cout << "Image filename shall be provided!" << endl;
        return -1;
    }

    cv::Mat img=cv::imread(argv[1]);
    
    if(img.data==NULL){
        cout << "Image filename not correct!" << endl;
        return -1;
    }

    cv::namedWindow("Example 1");
    cv::imshow("Example 1", img);
    cv::waitKey(0);

    return 0;
}