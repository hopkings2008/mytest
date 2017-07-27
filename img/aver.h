#pragma once

#include <string>
#include <err_msg.h>
#include <opencv2/opencv.hpp>

class ImageAverage{
    public:
        ImageAverage();
        ~ImageAverage();

        util::Error init(const std::string &file);

        util::Error average(cv::Mat &out);

        int chanNum() const;

    protected:
        cv::Mat m_ori; 
};
