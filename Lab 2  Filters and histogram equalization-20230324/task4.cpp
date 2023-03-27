#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main(int argc, char** argv){
    cv::Mat img=cv::imread(argv[1]);

    if(img.data==NULL){
        std::cout << "Image not found" << std::endl;
        return -1;
    }

    cv::namedWindow("Gray scale");
    cv::imshow("Gray scale", img);
    cv::waitKey(0);

    cv::Mat grayscale_img(img.rows, img.cols, CV_8U);
    cv::cvtColor(img, grayscale_img, cv::COLOR_BGR2GRAY, 0);

    //Computing histogram
    cv::Mat hist;
    int hist_size = 256;
    float range[] = {0, 256};
    const float* hist_range = {range};
    bool uniform = true, accumulate = false;
    calcHist(&grayscale_img, 1, 0, cv::Mat(), hist, 1, &hist_size, &hist_range, uniform, accumulate);

    //Plotting histogram
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / hist_size);
    cv::Mat histImage(hist_h, hist_w, CV_8U, cv::Scalar(0, 0, 0));
    normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    for (int i = 1; i < hist_size; i++) {
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             cv::Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
             cv::Scalar(255, 255, 255), 2, 8, 0);
    }

    cv::imshow("Histogram", histImage);
    cv::waitKey(0);

    return 0;

}