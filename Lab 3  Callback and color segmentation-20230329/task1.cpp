#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;

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

    cv::imshow("image", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}