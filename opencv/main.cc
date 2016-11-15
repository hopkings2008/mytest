#include <stdlib.h>
#include <string>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char *argv[]){
    int ret = 0;
    cv::Mat dst;
    cv::Mat img = cv::imread("./67769.jpg");
    if (img.empty()){
        printf("failed to load image.\n");
        return -1;
    }
    cv::Size ori = img.size();
    cv::Size dest;
    printf("ori: %d, %d\n", ori.width, ori.height);
    dest.width = ori.width/2;
    dest.height = ori.height/2;
    resize(img, dst, dest);
    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(95);
    cv::imwrite("dst.jpg", dst, compression_params);

    /*cv::namedWindow( "Example1", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Example1", img );
    cv::waitKey( 0 );
    cv::destroyWindow( "Example1" );*/
    return ret;
}
