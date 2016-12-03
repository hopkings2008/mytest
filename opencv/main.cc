#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

std::string type2str(int type);

int main(int argc, char *argv[]){
    int ret = 0;
    cv::Mat dst;
    //cv::Mat img = cv::imread("/home/zouyu/hopkings/pics/check.png", IMREAD_UNCHANGED );
    std::ifstream file("/home/zouyu/hopkings/pics/check.png", std::ios::in| std::ios::binary);
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    printf("len of file: %d\n", len);
    char * buf = new char[len];
    memset(buf, 0, len);
    file.read(buf, len);
    cv::Mat rawData = cv::Mat(1, len, CV_8UC1, (void *)buf);
    cv::Mat img = cv::imdecode(rawData, cv::IMREAD_UNCHANGED);
    if (img.empty()){
        printf("failed to load image.\n");
        return -1;
    }
    std::string type = type2str(img.type());
    printf("type: %s, %d*%d\n", type.c_str(), img.cols, img.rows);
    cv::Size ori = img.size();
    printf("ori: %d, %d\n", ori.width, ori.height);
    //dest.width = ori.width/2;
    //dest.height = ori.height/2;
    double ratew = ori.width/428.00;
    double rateh = ori.height/510.00;
    double rate = ratew > rateh ? ratew : rateh;
    rate = 1.0/rate;
    printf("rate: %f\n", rate);
    resize(img, dst, cv::Size(), rate, rate, cv::INTER_AREA);
    std::vector<int> compression_params;
    //compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    //compression_params.push_back(9);
    compression_params.push_back(IMWRITE_JPEG_QUALITY);
    compression_params.push_back(95);
    printf("dst rows: %d, cols: %d\n", dst.rows, dst.cols);
    //cv::imwrite("dstori.png", dst, compression_params);
    cv::Mat out = cv::Mat(dst.rows, dst.cols, CV_8UC3);
    int cols = 0;
    for (int i=0; i<dst.rows; i++){
        for (int j=0; j<dst.cols; j++){
            //out.at<Vec4b>(i, j)[3] = 0;
            out.at<Vec3b>(i, j)[2] = 255;
            out.at<Vec3b>(i, j)[1] = 255;
            out.at<Vec3b>(i, j)[0] = 255;
        }
    }
    for (int i=0; i<dst.rows; i++){
        for(int j=0; j<dst.cols; j++){
            /*if(dst.at<Vec4b>(i, j)[3] == 0){
                out.at<Vec3b>(i, j)[2] = 255;
                out.at<Vec3b>(i, j)[1] = 255;
                out.at<Vec3b>(i, j)[0] = 255;
                continue;
            }*/
            if (dst.at<Vec4b>(i, j)[3] == 0){
                continue;
            }
            out.at<Vec3b>(i, j)[2] = dst.at<Vec4b>(i,j)[2];
            out.at<Vec3b>(i, j)[1] = dst.at<Vec4b>(i,j)[1];
            out.at<Vec3b>(i, j)[0] = dst.at<Vec4b>(i,j)[0];
        }
    }
    cv::imwrite("./out1.jpg", out, compression_params);
    /*for (int i=0; i<dst.rows; i++){
        for(int j=0; j<dst.cols; j++){
            if(dst.at<Vec4b>(i, j)[3] ==0){
                if(cols < j){
                    cols = j;
                }
                dst.at<Vec3b>(i, j)[2] = 255;
                dst.at<Vec3b>(i, j)[1] = 255;
                dst.at<Vec3b>(i, j)[0] = 255;
            }
        }
    }*/
    printf("cols: %d\n", cols);
    //cv::imwrite("dst.jpg", dst, compression_params);
    //std::vector<unsigned char> out;
    //cv::encode(".png", dst, out, compression_params);

    /*cv::namedWindow( "Example1", cv::WINDOW_AUTOSIZE );
      cv::imshow( "Example1", img );
      cv::waitKey( 0 );
      cv::destroyWindow( "Example1" );*/
    return ret;
}

std::string type2str(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }

    r += "C";
    r += (chans+'0');

    return r;
}
