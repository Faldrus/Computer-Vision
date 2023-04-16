#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
    if(argc<2){
        cout << "Image filename shall be provided!" << endl;
        return -1;
    }
    if(!filesystem::exists("./output"))
        filesystem::create_directory("./output");

    Mat image=imread(argv[1]);
    if(image.data==NULL){
        cout << "Image not found!" << endl;
        return -1;
    }

    //task1
    namedWindow("Image");
    imshow("Image", image);
    waitKey(0);
    destroyWindow("Image");
    
    Mat blur;                                                                           //blurred image for improved edge detection
    GaussianBlur(image, blur, Size(9, 9), 0);
    Mat canny;                                                                          //canny image
    Canny(blur, canny, 50, 200);
    namedWindow("Canny");
    imshow("Canny", canny);
    waitKey(0);
    imwrite("./output/canny.png", canny);
    createTrackbar("low", "Canny", 0, 255, NULL);
    createTrackbar("high", "Canny", 0, 255, NULL);
    Mat canny2=canny.clone();
    while(true){
        int low=getTrackbarPos("low", "Canny");
        int high=getTrackbarPos("high", "Canny");
        Canny(blur, canny2, low, high);
        imshow("Canny", canny2);
        if(waitKey(10)==32) break;                                                      //press space to exit
    }
    destroyWindow("Canny");
    
    //TASK2&3
    //Two vectors to store the lines since they have different theta ranges
    vector<Vec2f> llane;                                                                //left lines
    vector<Vec2f> rlane;                                                                //right lines       
    HoughLines(canny, llane, 1, CV_PI / 180, 100, 0, 0, 0, CV_PI / 3);
    HoughLines(canny, rlane, 1, CV_PI / 180, 100, 0, 0, -CV_PI / 3, 0);
    Vec2f lline=llane[0];                       
    Vec2f rline=rlane[0]; 

    float lrho=lline[0], rrho = rline[0], ltheta = lline[1], rtheta = rline[1];
    for(int i=0; i<canny.rows; i++){
        for(int j=0; j<canny.cols; j++){
            if(i>lrho/sin(ltheta)-j/tan(ltheta) && i>rrho/sin(rtheta)-j/tan(rtheta)){   //if the point is above the left and right lines
                image.at<Vec3b>(i,j)=Vec3b(0,0,255);                                    //set pixel to red                 
            }
        }
    }
    namedWindow("Hough lines");
    imshow("Hough lines", image);
    waitKey(0);
    imwrite("./output/hough_lines.png", image);
    destroyWindow("Hough lines");

    //task4
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT_ALT, 1.5, 20, 300, 0.9, 5, 50);
    for(int i=0; i<circles.size(); i++){
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(image, center, radius, cv::Scalar(82, 249, 138), -1, 8, 0);
    }

    namedWindow("Hough circles"); 
    imshow("Hough circles", image);
    waitKey(0);
    imwrite("./output/hough_circles.png", image);
    destroyWindow("Hough circles");
    


    return 0;
}