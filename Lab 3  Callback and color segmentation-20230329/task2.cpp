#include <opencv2/highgui.hpp>
#include <iostream>

#define NEIGHBORHOOD_X 9
#define NEIGHBORHOOD_Y 9

using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata){
    if(event==cv::EVENT_LBUTTONDOWN){
        cv::Mat image=*(cv::Mat*)userdata;
        cv::Vec3b pixel=image.at<cv::Vec3b>(y,x);
        cout << "BGR pixel values: " << pixel << endl;
    }
}

int main(int argc, char** argv){
    if(argc<2){
        cout << "Image filename shall be provided!" << endl;
        return -1;
    }

    cv::Mat image = cv::imread(argv[1]);
    if(image.data==NULL){
        cout << "Image not found!" << endl;
        return -1;
    }

    cv::namedWindow("Image");
    cv::imshow("Image", image);
    cv::setMouseCallback("Image", onMouse, (void*)&image);
    
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}