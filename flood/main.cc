#include <opencv2/opencv.hpp>    
#include <opencv2/imgproc/imgproc.hpp>    
using namespace cv;    
int main(int argc, char *argv[])  
{      
    Mat src = imread(argv[1]);   
    imshow("【原始图】",src);  
    Rect ccomp; 
    int flags = 8 | cv::FLOODFILL_FIXED_RANGE | (47<<8) ;
    floodFill(src, Point(0,0), Scalar(1, 0, 0), &ccomp, Scalar(0, 0, 0),Scalar(0, 0, 0),  flags);  
    imshow("【效果图】",src);  
    waitKey(0);  
    return 0;      
} 
