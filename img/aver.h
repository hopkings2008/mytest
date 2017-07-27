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
        int colNum() const;
        int rowNum() const;

        // name: doesn't have suffix.
        util::Error save(const std::string &path, const std::string &name);

    protected:
        std::string pathJoin(const std::string &p1, const std::string &p2);

    protected:
        cv::Mat m_ori; 
};
