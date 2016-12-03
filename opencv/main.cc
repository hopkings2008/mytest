
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

void convert(const cv::Mat &matResize, cv::Mat &dst);
int getChannelNum(const cv::Mat &mat);

int main(int argc, char *argv[]){
    double w = 140;
    double h = 140;
    std::ifstream file("/home/zouyu/hopkings/pics/check.png", std::ios::binary);
    file.seekg(0, file.end);
    int data_size = file.tellg();
    file.seekg(0, file.beg);
    printf("data_size: %d\n", data_size);
    unsigned char *data = new unsigned char[data_size];
    file.read((char *)data, data_size);
    file.close();

    std::vector<unsigned char> out;
    cv::Mat matResize;
    cv::Mat rawData = cv::Mat(1, data_size, CV_8UC1, (void *)data);
    cv::Mat img = cv::imdecode(rawData, cv::IMREAD_UNCHANGED);
    if (img.empty()){
        printf("faied to imdecode\n");
        return -1;
    }
    cv::Size oriSize = img.size();
    int channelNum = getChannelNum(img);
    double wRate = double(oriSize.width)/w;
    double hRate = double(oriSize.height)/h;
    double rate = wRate > hRate ? wRate : hRate;
    rate = 1.0/rate;
    // only resize the image if it is larger than the specified area.
    if (rate < 1.0){
        cv::resize(img, matResize, cv::Size(), rate, rate, cv::INTER_AREA);
        if (matResize.empty()){
            printf("failed to resize.\n");
            return -1;
        }
        std::vector<int> compression_params;
        compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression_params.push_back(95);
        if (channelNum == 4){
            cv::Mat dst = cv::Mat(matResize.rows, matResize.cols, CV_8UC3);
            convert(matResize, dst);

            /*for(int i=0; i<matResize.rows; i++){
              for(int j=0; j<matResize.cols; j++){
              dst.at<cv::Vec3b>(i, j)[2] = 255;
              dst.at<cv::Vec3b>(i, j)[1] = 255;
              dst.at<cv::Vec3b>(i, j)[0] = 255;
              }
              }
              for(int i=0; i<matResize.rows; i++){
              for(int j=0; j<matResize.cols; j++){
              if (matResize.at<cv::Vec4b>(i, j)[3] == 0){
              continue;
              }
              dst.at<cv::Vec3b>(i, j)[2] = matResize.at<cv::Vec4b>(i, j)[2];
              dst.at<cv::Vec3b>(i, j)[1] = matResize.at<cv::Vec4b>(i, j)[1];
              dst.at<cv::Vec3b>(i, j)[0] = matResize.at<cv::Vec4b>(i, j)[0];
              }
              }*/
            printf("rows %d, cols %d\n", dst.rows, dst.cols);
            cv::imwrite("/home/zouyu/hopkings/mytest/opencv/s.jpg", dst, compression_params);
            if (!cv::imencode(".jpg", dst, out, compression_params)){
                printf("failed to encode.\n");
            }
            printf("out size: %ld\n", out.size());
            std::ofstream outfile("/home/zouyu/hopkings/mytest/opencv/t.jpg", std::ios::out | std::ios::binary);
            outfile.write((char *)out.data(), out.size());
            outfile.close();

        }
    }
}

void convert(const cv::Mat &matResize, cv::Mat &dst){
    for (int i=0; i<matResize.rows; i++){
        for(int j=0; j<matResize.cols; j++){
            dst.at<cv::Vec3b>(i, j)[2] = 255;
            dst.at<cv::Vec3b>(i, j)[1] = 255;
            dst.at<cv::Vec3b>(i, j)[0] = 255;
        }
    }
    for(int i=0; i<matResize.rows; i++){
        for(int j=0; j<matResize.cols; j++){
            if (matResize.at<cv::Vec4b>(i, j)[3] == 0){
                continue;
            }
            dst.at<cv::Vec3b>(i, j)[2] = matResize.at<cv::Vec4b>(i, j)[2];
            dst.at<cv::Vec3b>(i, j)[1] = matResize.at<cv::Vec4b>(i, j)[1];
            dst.at<cv::Vec3b>(i, j)[0] = matResize.at<cv::Vec4b>(i, j)[0];
        }
    }
}

int getChannelNum(const cv::Mat &mat){
    int type = mat.type();
    return 1 + (type >> CV_CN_SHIFT);
}
