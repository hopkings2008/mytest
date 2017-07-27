#include <aver.h>
#include <vector>

ImageAverage::ImageAverage(){
}

ImageAverage::~ImageAverage(){
}

util::Error ImageAverage::init(const std::string &file){
    util::Error err;
    m_ori = cv::imread(file.c_str(), CV_LOAD_IMAGE_UNCHANGED);
    if (m_ori.empty()){
        err.setCode(-1);
        err.errorf("failed to read image from %s", file.c_str());
        return err;
    }
    return  err;
}

int ImageAverage::chanNum() const {
    int type = m_ori.type();
    return 1 + (type >> CV_CN_SHIFT);
}

int ImageAverage::colNum() const {
    return m_ori.cols;
}

int ImageAverage::rowNum() const {
    return m_ori.rows;
}

std::string ImageAverage::pathJoin(const std::string &p1, const std::string &p2){
    std::string full = p1;
    if (full[full.length()-1] != '/'){
        full += "/";
    }
    full += p2;
    return full;
}

util::Error ImageAverage::save(const std::string &path, const std::string &name){
    util::Error err;
    int chans = chanNum();
    std::string suffix = ".jpeg";
    std::vector<int> params;
    switch (chans){
        case 4:
            {
                suffix = ".png";
                params.push_back(CV_IMWRITE_PNG_COMPRESSION);
                params.push_back(3);
                break;
            }
        default:
            {
                suffix = ".jpeg";
                params.push_back(CV_IMWRITE_JPEG_QUALITY);
                params.push_back(95);
                break;
            }
    }
    std::string full = pathJoin(path, name);
    full += suffix;
    if (!imwrite(full.c_str(), m_ori, params)){
        err.setCode(-1);
        err.errorf("failed to save image to %s", full.c_str());
        return err;
    }
    return err;
}

util::Error ImageAverage::average(cv::Mat &out){
    util::Error err;
    int range = 2;
    int chans = chanNum();
    for (int i = 0; i<m_ori.rows; i++){
        for (int j = 0; j<m_ori.cols; j++){
            if (4 == chans){
                cv::Vec4b v;
                for (int k = i-1; k<range; k++){
                    for (int l = j-1; l<range; l++){
                        if (k < 0 || l < 0 || k >= m_ori.rows || l >= m_ori.cols || (k == i && l == j)){
                            continue;
                        }
                        v[0] += m_ori.at<cv::Vec4b>(k,l)[0];
                        v[1] += m_ori.at<cv::Vec4b>(k,l)[1];
                        v[2] += m_ori.at<cv::Vec4b>(k,l)[2];
                    }
                }
                out.at<cv::Vec4b>(i,j)[0] = v[0]/8;
                out.at<cv::Vec4b>(i,j)[1] = v[1]/8;
                out.at<cv::Vec4b>(i,j)[2] = v[2]/8;
                out.at<cv::Vec4b>(i,j)[3] = m_ori.at<cv::Vec4b>(i,j)[3];
                continue;
            }

            cv::Vec3b v;
            for (int k = i-1; k<range; k++){
                for (int l = j-1; l<range; l++){
                    if (k < 0 || l < 0 || k >= m_ori.rows || l >= m_ori.cols || (k == i && l == j)){
                        continue;
                    }
                    v[0] += m_ori.at<cv::Vec3b>(k,l)[0];
                    v[1] += m_ori.at<cv::Vec3b>(k,l)[1];
                    v[2] += m_ori.at<cv::Vec3b>(k,l)[2];
                }
            }
            out.at<cv::Vec3b>(i,j)[0] = v[0]/8;
            out.at<cv::Vec3b>(i,j)[1] = v[1]/8;
            out.at<cv::Vec3b>(i,j)[2] = v[2]/8;
        }
    }
    return err;
}
