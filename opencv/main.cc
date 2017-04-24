
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
int testcopy();
int tailor(const unsigned char *data, size_t data_size, std::vector<unsigned char> &out);

int main(int argc, char *argv[]){
    std::ifstream file("/home/zouyu/hopkings/pics/1.jpg", std::ios::binary);
    file.seekg(0, file.end);
    int data_size = file.tellg();
    file.seekg(0, file.beg);
    printf("data_size: %d\n", data_size);
    unsigned char *data = new unsigned char[data_size];
    file.read((char *)data, data_size);
    file.close();
    std::vector<unsigned char> out;
    int ret = tailor(data, data_size, out);
    if (ret != 0){
        printf("failed to tailor\n");
        return ret;
    }

    std::ofstream outfile("/home/zouyu/hopkings/mytest/opencv/test.jpg", std::ios::out | std::ios::binary);
    outfile.write((char *)out.data(), out.size());
    outfile.close();



    /*std::vector<unsigned char> out;
      cv::Mat matResize;
      cv::Mat rawData = cv::Mat(1, data_size, CV_8UC1, (void *)data);
      cv::Mat img = cv::imdecode(rawData, cv::IMREAD_UNCHANGED);
      if (img.empty()){
      printf("faied to imdecode\n");
      return -1;
      }
      cv::imwrite("ori.jpeg", img, std::vector<int>());
      cv::Size oriSize = img.size();
      int channelNum = getChannelNum(img);
      double wRate = double(oriSize.width)/w;
      double hRate = double(oriSize.height)/h;
      double rate = wRate > hRate ? wRate : hRate;
      if (channelNum ==4){
      cv::Mat dst = cv::Mat(img.rows, img.cols, CV_8UC3);
      convert(img, dst);
      cv::imwrite("ori2.jpeg", dst, std::vector<int>());
      }
      rate = 1.0/rate;
    // only resize the image if it is larger than the specified area.
    if (rate < 1.0){
    cv::resize(img, matResize, cv::Size(), rate, rate, cv::INTER_AREA);
    if (matResize.empty()){
    printf("failed to resize.\n");
    return -1;
    }
    std::vector<int> params;
    params.push_back(cv::IMWRITE_PNG_COMPRESSION );
    params.push_back(9);
    cv::imwrite("t1.jpg", matResize, params);
    if (!cv::imencode(".jpg", matResize, out, params)){
    printf("failed to save to png.\n");
    return -1;
    }
    //std::ofstream outfile("/home/zouyu/hopkings/mytest/opencv/t.jpg", std::ios::out | std::ios::binary);
    //outfile.write((char *)out.data(), out.size());
    //outfile.close();
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(95);
    if (channelNum == 4){
    cv::Mat dst = cv::Mat(matResize.rows, matResize.cols, CV_8UC3);
    convert(matResize, dst);
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
    }*/
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
                printf("find alpha = 0\n");
                continue;
            }
            dst.at<cv::Vec3b>(i, j)[2] = matResize.at<cv::Vec4b>(i, j)[2];
            dst.at<cv::Vec3b>(i, j)[1] = matResize.at<cv::Vec4b>(i, j)[1];
            dst.at<cv::Vec3b>(i, j)[0] = matResize.at<cv::Vec4b>(i, j)[0];
        }
    }
}

void overLap(cv::Mat &source, cv::Mat &dst, int x, int y){
    if (dst.cols < source.cols || dst.rows < source.rows){
        return;
    }
    source.copyTo(dst(cv::Rect(x, y, source.cols, source.rows)));
}

int testcopy(){
    std::string src = "qrcode.png";
    std::string small = "logo.png";
    std::ifstream file(src, std::ios::binary);
    file.seekg(0, file.end);
    int data_size = file.tellg();
    file.seekg(0, file.beg);
    printf("data_size: %d\n", data_size);
    unsigned char *data = new unsigned char[data_size];
    file.read((char *)data, data_size);
    file.close();

    cv::Mat rawData = cv::Mat(1, data_size, CV_8UC1, (void *)data);
    cv::Mat img = cv::imdecode(rawData, cv::IMREAD_UNCHANGED);
    if (img.empty()){
        printf("faied to imdecode\n");
        return -1;
    }
    std::ifstream file2(small, std::ios::binary);
    file2.seekg(0, file2.end);
    data_size = file2.tellg();
    file2.seekg(0, file2.beg);
    printf("data_size: %d\n", data_size);
    data = new unsigned char[data_size];
    file2.read((char *)data, data_size);
    file2.close();
    cv::Mat rawData2 = cv::Mat(1, data_size, CV_8UC1, (void *)data);
    cv::Mat logo = cv::imdecode(rawData2, cv::IMREAD_UNCHANGED);
    if (logo.empty()){
        printf("failed to imdecode logo\n");
        return -1;
    }
    int xc = img.cols/2;
    int yc = img.cols/2;
    int x = xc - logo.cols/2;
    int y = yc - logo.rows/2;
    overLap(logo, img, x, y);

    std::vector<unsigned char> out;
    std::vector<int> params;
    params.push_back(cv::IMWRITE_PNG_COMPRESSION );
    params.push_back(9);
    if (!cv::imencode(".png", img, out, params)){
        printf("failed to save to png.\n");
        return -1;
    }
    std::ofstream outfile("/home/zouyu/hopkings/mytest/opencv/myqrcode.png", std::ios::out | std::ios::binary);
    outfile.write((char *)out.data(), out.size());
    outfile.close();
    return 0;
}

int getChannelNum(const cv::Mat &mat){
    int type = mat.type();
    return 1 + (type >> CV_CN_SHIFT);
}


int tailor(const unsigned char *data, size_t data_size, std::vector<unsigned char> &out){
    try {
        cv::Mat rawData = cv::Mat(1, data_size, CV_8UC1, (void *)data);
        cv::Mat img = cv::imdecode(rawData, cv::IMREAD_UNCHANGED);
        if (img.empty()){
            printf("failed to decode image.");
            return -1;
        }
        int channelNum = getChannelNum(img);
        int flag = channelNum == 4 ? CV_8UC4 : CV_8UC3;
        int w = img.cols;
        int h = img.rows;
        int edge = h > w ? w : h;
        int x = (w - edge) / 2;
        int y = (h - edge) / 2;
        cv::Mat dst = cv::Mat(edge, edge, flag);
        for (int i = y; i < edge; i++){
            for (int j = x; j < edge; j++){
                switch(flag){
                    case CV_8UC4:
                        {
                            dst.at<cv::Vec4b>(i-y, j-x)[3] = img.at<cv::Vec4b>(i, j)[3];
                            dst.at<cv::Vec4b>(i-y, j-x)[2] = img.at<cv::Vec4b>(i, j)[2];
                            dst.at<cv::Vec4b>(i-y, j-x)[1] = img.at<cv::Vec4b>(i, j)[1];
                            dst.at<cv::Vec4b>(i-y, j-x)[0] = img.at<cv::Vec4b>(i, j)[0];
                            break;
                        }
                    default:
                        {
                            dst.at<cv::Vec3b>(i-y, j-x)[2] = img.at<cv::Vec3b>(i, j)[2];
                            dst.at<cv::Vec3b>(i-y, j-x)[1] = img.at<cv::Vec3b>(i, j)[1];
                            dst.at<cv::Vec3b>(i-y, j-x)[0] = img.at<cv::Vec3b>(i, j)[0];
                            break;
                        }
                }
            }
        }

        std::vector<int> compression_params;
        std::string suffix = ".jpg";
        switch (flag){
            case CV_8UC4:
                {
                    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
                    compression_params.push_back(3);
                    suffix = ".png";
                    break;
                }
            default:
                {
                    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
                    compression_params.push_back(95);
                    break;
                }
        }

        if(!cv::imencode(suffix, dst, out, compression_params)){
            printf("failed to encode to %s for image %d:%d", suffix.c_str(), dst.cols, dst.rows);
            return -1;
        }

        return 0;
    }
    catch(cv::Exception &e){
        printf("caught opencv exception: %s", e.what());
        return -1;
    }
}
