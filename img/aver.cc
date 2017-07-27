#include <aver.h>

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

util::Error ImageAverage::average(cv::Mat &out){
    util::Error err;
    return err;
}
