#include <aver.h>
#include <vector>

ImageAverage::ImageAverage():m_range(3){
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

int ImageAverage::depth() const {
    int s = m_ori.depth();
    switch (s){
        case CV_8U:
            {
                return (1<<8)-1;
            }
        case CV_16U:
            {
                return (1<<16)-1;
            }
        default:
            {
                break;
            }
    }
    return 0;
}

void ImageAverage::setRange(int range){
    m_range = range;
}

std::string ImageAverage::pathJoin(const std::string &p1, const std::string &p2){
    std::string full = p1;
    if (full[full.length()-1] != '/'){
        full += "/";
    }
    full += p2;
    return full;
}

util::Error ImageAverage::save(const cv::Mat &img, const std::string &path, const std::string &name){
    util::Error err;
    int chans = chanNum();
    std::string suffix = ".jpg";
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
                suffix = ".jpg";
                params.push_back(CV_IMWRITE_JPEG_QUALITY);
                params.push_back(95);
                break;
            }
    }
    std::string full = pathJoin(path, name);
    full += suffix;
    if (!imwrite(full.c_str(), img, params)){
        err.setCode(-1);
        err.errorf("failed to save image to %s", full.c_str());
        return err;
    }
    return err;
}

util::Error ImageAverage::averageGray(cv::Mat &out){
    util::Error err;
    cv::Mat gray;
    cv::cvtColor(m_ori, gray, CV_RGB2GRAY);
    cv::Mat grayout(gray.rows, gray.cols, CV_8UC1);
    int minus = (m_range - 1)/2;
    for (int i=0; i<gray.rows; i++){
        for (int j=0; j<gray.cols; j++){
            int k = 0;
            int l = 0;
            int total = 0;
            double v = 0.0;
            for (int m = 0; m<m_range; m++){
                for (int n = 0; n<m_range; n++){
                    k = i-minus + m;
                    l = j-minus + n;
                    if (k < 0 || l < 0 || k >= gray.rows || l >= gray.cols){
                        continue;
                    }
                    v += gray.at<unsigned char>(k,l);
                    total++;
                }
            }

            grayout.at<unsigned char>(i,j) = (unsigned char)(v/total);
        }
    }

    cv::cvtColor(grayout, out, CV_GRAY2RGB);
    return err;
}

util::Error ImageAverage::average2(cv::Mat &out){
    util::Error err;
    std::vector<cv::Mat> channels;
    cv::Mat imgy;
    cv::cvtColor(m_ori, imgy, CV_BGR2YCrCb);
    cv::split(imgy,channels);

    cv::Mat &gray = channels[0];
    cv::Mat grayout(gray.rows, gray.cols, CV_8UC1);
    int minus = (m_range - 1)/2;
    for (int i=0; i<gray.rows; i++){
        for (int j=0; j<gray.cols; j++){
            int k = 0;
            int l = 0;
            int total = 0;
            double v = 0.0;
            for (int m = 0; m<m_range; m++){
                for (int n = 0; n<m_range; n++){
                    k = i-minus + m;
                    l = j-minus + n;
                    if (k < 0 || l < 0 || k >= gray.rows || l >= gray.cols){
                        continue;
                    }
                    v += gray.at<unsigned char>(k,l);
                    total++;
                }
            }

            grayout.at<unsigned char>(i,j) = (unsigned char)(v/total);
        }
    }

    for (int i=0; i<gray.rows; i++){
		for (int j=0; j<gray.cols; j++){
			gray.at<unsigned char>(i,j) = grayout.at<unsigned char>(i,j);
		}
	}

	cv::merge(channels, imgy);
    cvtColor(imgy, out, CV_YCrCb2BGR);
    return err;
}




util::Error ImageAverage::average(cv::Mat &out){
    util::Error err;
    //cv::medianBlur(m_ori, out, 3);
    //cv::cvSmooth(m_ori, out);
    //cv::Laplacian(m_ori, out, CV_16S, 3, 1, 0, cv::BORDER_DEFAULT );
    //cv::GaussianBlur(m_ori, out, cv::Size(3,3) ,0 ,0);
    //return err;
    std::vector<cv::Mat> channels;
    cv::Mat imgy;
    cv::cvtColor(m_ori, imgy, CV_BGR2YCrCb);
    cv::split(imgy,channels);
    /*cv::medianBlur(channels[0], channels[0], 3);
    cv::merge(channels, imgy);
    cvtColor(imgy, out, CV_YCrCb2BGR);
    return err;*/
    //cv::Mat &imgTmp = channels[0];
    cv::Mat imgTmp(m_ori.rows, m_ori.cols, CV_8UC3);
    int chans = chanNum();
    int minus = (m_range-1)/2;
    for (int i = 0; i<channels[0].rows; i++){
        for (int j = 0; j<channels[0].cols; j++){
            int total = 0;
            if (4 == chans){
                cv::Vec4b v;
                int k = 0;
                int l = 0;
                for (int m = 0; m<m_range; m++){
                    for (int n = 0; n<m_range; n++){
                        k = i - minus + m;
                        l = j-minus + n;
                        if (k < 0 || l < 0 || k >= imgTmp.rows || l >= imgTmp.cols){
                            continue;
                        }
                        v[0] += imgTmp.at<cv::Vec4b>(k,l)[0];
                        v[1] += imgTmp.at<cv::Vec4b>(k,l)[1];
                        v[2] += imgTmp.at<cv::Vec4b>(k,l)[2];
                        total++;
                    }
                }
                
                out.at<cv::Vec4b>(i,j)[0] = v[0]/total;
                out.at<cv::Vec4b>(i,j)[1] = v[1]/total;
                out.at<cv::Vec4b>(i,j)[2] = v[2]/total;
                out.at<cv::Vec4b>(i,j)[3] = imgTmp.at<cv::Vec4b>(i,j)[3];
                continue;
            }

            cv::Vec3b v;
            int k = 0;
            int l = 0;
            for (int m = 0; m<m_range; m++){
                for (int n = 0; n<m_range; n++){
                    k = i-minus + m;
                    l = j-minus + n;
                    if (k < 0 || l < 0 || k >= imgTmp.rows || l >= imgTmp.cols){
                        continue;
                    }
                    v[0] += channels[0].at<cv::Vec3b>(k,l)[0];
                    v[1] += channels[0].at<cv::Vec3b>(k,l)[1];
                    v[2] += channels[0].at<cv::Vec3b>(k,l)[2];
                    total++;
                }
            }
            //imgTmp.at<cv::Vec3b>(i,j)[0] = channels[0].at<cv::Vec3b>(i,j)[0]-1;
            imgTmp.at<cv::Vec3b>(i,j)[0] = static_cast<unsigned char>(round((double)v[0]/(double)total));
            imgTmp.at<cv::Vec3b>(i,j)[1] = static_cast<unsigned char>(round((double)v[1]/(double)total));
            imgTmp.at<cv::Vec3b>(i,j)[2] = static_cast<unsigned char>(round((double)v[2]/(double)total));
            //imgTmp.at<cv::Vec3b>(i,j)[1] = channels[0].at<cv::Vec3b>(i,j)[1];
            //imgTmp.at<cv::Vec3b>(i,j)[2] = channels[0].at<cv::Vec3b>(i,j)[2];
            //out.at<cv::Vec3b>(i,j)[1] = imgTmp.at<cv::Vec3b>(i,j)[1];
            //out.at<cv::Vec3b>(i,j)[2] = imgTmp.at<cv::Vec3b>(i,j)[2];
            //out.at<cv::Vec3b>(i,j)[1] = static_cast<unsigned char>(round((double)v[1]/(double)total));
            //out.at<cv::Vec3b>(i,j)[2] = static_cast<unsigned char>(round((double)v[2]/(double)total));
            //out.at<cv::Vec3b>(i,j)[0] = imgTmp.at<cv::Vec3b>(i,j)[0];
            //out.at<cv::Vec3b>(i,j)[1] = imgTmp.at<cv::Vec3b>(i,j)[1];
            //out.at<cv::Vec3b>(i,j)[2] = imgTmp.at<cv::Vec3b>(i,j)[2];
        }
    }
    for (int i = 0; i< channels[0].rows; i++){
            for (int j = 0; j<channels[0].cols; j++){
                    channels[0].at<cv::Vec3b>(i,j)[0] = imgTmp.at<cv::Vec3b>(i,j)[0];
                    channels[0].at<cv::Vec3b>(i,j)[1] = imgTmp.at<cv::Vec3b>(i,j)[1];
                    channels[0].at<cv::Vec3b>(i,j)[2] = imgTmp.at<cv::Vec3b>(i,j)[2];
            }
    }
    cv::merge(channels, imgy);
    cvtColor(imgy, out, CV_YCrCb2BGR);
    return err;
}

util::Error ImageAverage::inverse(cv::Mat &out){
    util::Error err;
    int chans = chanNum();
    int max = depth();

    for (int i=0; i < m_ori.rows; i++){
        for (int j=0; j<m_ori.cols; j++){
            if (4 == chans){
                out.at<cv::Vec4b>(i,j)[3] = m_ori.at<cv::Vec4b>(i,j)[3];
                out.at<cv::Vec4b>(i,j)[2] = max - m_ori.at<cv::Vec4b>(i,j)[2];
                out.at<cv::Vec4b>(i,j)[1] = max - m_ori.at<cv::Vec4b>(i,j)[1];
                out.at<cv::Vec4b>(i,j)[0] = max - m_ori.at<cv::Vec4b>(i,j)[0];
                continue;
            }
            out.at<cv::Vec3b>(i,j)[2] = max - m_ori.at<cv::Vec3b>(i,j)[2];
            out.at<cv::Vec3b>(i,j)[1] = max - m_ori.at<cv::Vec3b>(i,j)[1];
            out.at<cv::Vec3b>(i,j)[0] = max - m_ori.at<cv::Vec3b>(i,j)[0];
        }
    }
    return err;
}
