#include <opencv2/highgui.hpp>
#include <iostream>

#define NEIGHBORHOOD_X 9
#define NEIGHBORHOOD_Y 9

using namespace std;

void onMouse(int event, int x, int y, int flags, void* userdata){
    if(event==cv::EVENT_LBUTTONDOWN){
        cv::Mat image=*(cv::Mat*)userdata;
        cv::Mat output=image.clone();

        //Prevents segmentation fault looking outside image boundaries
        if(y+NEIGHBORHOOD_Y>output.rows || x+NEIGHBORHOOD_X>output.cols){
            return;
        }

        //Creates a rectangle around the pixel
        cv::Rect rect(x, y, NEIGHBORHOOD_X, NEIGHBORHOOD_Y);
        //Calculate mean of 9x9 neighborhood
        cv::Scalar mean = cv::mean(output(rect));
        cout << "BGR mean: " << mean << endl;
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