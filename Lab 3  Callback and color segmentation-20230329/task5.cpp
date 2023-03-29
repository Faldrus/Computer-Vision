#include <opencv2/highgui.hpp>
#include <iostream>
#include <filesystem>

#define NEIGHBORHOOD_X 9
#define NEIGHBORHOOD_Y 9
#define THRESHOLD 90

using namespace std;

bool PREDEFINED = false;

void onMouse(int event, int x, int y, int flags, void* userdata){
    if(event==cv::EVENT_LBUTTONDOWN){
        cv::Mat image=*(cv::Mat*)userdata;
        cv::Mat output=image.clone();

        //Prevents segmentation fault looking outside image boundaries
        if(y+NEIGHBORHOOD_Y>output.rows || x+NEIGHBORHOOD_X>output.cols){
            return;
        }

        //TASK 3
        //Creates a rectangle around the pixel
        cv::Rect rect(x, y, NEIGHBORHOOD_X, NEIGHBORHOOD_Y);
        //Calculate mean of 9x9 neighborhood
        cv::Scalar mean = cv::mean(output(rect));
        cout << "BGR mean: " << mean << endl;

        //TASK 4
        //Create a mask
        if(PREDEFINED){
            mean=cv::Vec3b(92, 37, 201);
        }
        cv::Mat mask(image.rows, image.cols, CV_8U);
        for(int i=0; i<image.rows; i++){
            for(int j=0; j<image.cols; j++){
                cv::Vec3b pixel=image.at<cv::Vec3b>(i,j);
                if(abs(pixel[0]-mean[0])<THRESHOLD && abs(pixel[1]-mean[1])<THRESHOLD && abs(pixel[2]-mean[2])<THRESHOLD)
                    mask.at<uchar>(i,j)=255;
                else 
                    mask.at<uchar>(i,j)=0;
            }
        }
        cv::imshow("Mask", mask);
        if(PREDEFINED)
            cv::imwrite("./output/mask_predefined.png", mask);
        else
            cv::imwrite("./output/mask.png", mask);

        //TASK 5
        cv::Vec3b color=cv::Vec3b(static_cast<uchar>(mean[0]), static_cast<uchar>(mean[1]), static_cast<uchar>(mean[2]));
        cv::Mat mask2(image.rows, image.cols, CV_8UC3);
        for(int i=0; i<image.rows; i++){
            for(int j=0; j<image.cols; j++){
                if(mask.at<uchar>(i,j)==255)
                    mask2.at<cv::Vec3b>(i,j)=color;
                else
                    mask2.at<cv::Vec3b>(i,j)=image.at<cv::Vec3b>(i,j);
			}
		}
        cv::imshow("Mask 2", mask2);
        if(PREDEFINED)
            cv::imwrite("./output/mask2_predefined.png", mask);
        else
            cv::imwrite("./output/mask2.png", mask);
    }
}

int main(int argc, char** argv){
    if(argc<2){
        cout << "Image filename shall be provided!" << endl;
        return -1;
    }

    cv::Mat image=cv::imread(argv[1]);
    if(image.data==NULL){
        cout << "Image not found!" << endl;
        return -1;
    }else{
        filesystem::create_directory("./output");
    }

    if(argc>2 && string(argv[2])=="predefined"){
        PREDEFINED = true;
    }

    cv::namedWindow("Image");
    cv::imshow("Image", image);
    cv::setMouseCallback("Image", onMouse, (void*)&image);
    
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}