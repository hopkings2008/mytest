#include <string>
#include <vector>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>

#define FACE_DOWNSAMPLE_RATIO 1.5

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{  
    try
    {
        if (argc == 1)
        {
            cout << "Give some image files as arguments to this program." << endl;
            return 0;
        }

        printf("begin to get face detector.\n");
        timeval tg1, tg2;
        gettimeofday(&tg1, NULL);
        frontal_face_detector detector = get_frontal_face_detector();
        gettimeofday(&tg2, NULL);
        uint64_t total_time = (tg2.tv_sec - tg1.tv_sec ) * 1000 + (tg2.tv_usec - tg1.tv_usec) / 1000;
        printf("get face time: %ld\n", total_time);
        //image_window win;

        // Loop over all the images provided on the command line.
        for (int i = 1; i < argc; ++i)
        {
            cout << "processing image " << argv[i] << endl;
            cv::Mat cvimg = cv::imread(argv[i], 1);
            cv::Mat ims;
            cv::Mat grayImg;
            int w = cvimg.cols;
            int h = cvimg.rows;
            //float raio = w/320 > h/180 ? h/180 : w/320;
            float raio = 1.0;
            //cv::resize(cvimg, ims, cv::Size(), 1.0/raio, 1.0/raio);
            cv::cvtColor(cvimg, grayImg, cv::COLOR_BGR2GRAY);
            printf("origin w: %d, h: %d\n", w, h);
            int edge = w > h ? h : w;
            dlib::cv_image<unsigned char> img(grayImg);
            //array2d<unsigned char> img;
            //load_image(img, argv[i]);
            // Make the image bigger by a factor of two.  This is useful since
            // the face detector looks for faces that are about 80 by 80 pixels
            // or larger.  Therefore, if you want to find faces that are smaller
            // than that then you need to upsample the image as we do here by
            // calling pyramid_up().  So this will allow it to detect faces that
            // are at least 40 by 40 pixels in size.  We could call pyramid_up()
            // again to find even smaller faces, but note that every time we
            // upsample the image we make the detector run slower since it must
            // process a larger image.
            //pyramid_up(img);

            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces it can find in the image.
            gettimeofday(&tg1, NULL);
            std::vector<rectangle> dets = detector(img);
            gettimeofday(&tg2, NULL);
            total_time = (tg2.tv_sec - tg1.tv_sec ) * 1000 + (tg2.tv_usec - tg1.tv_usec) / 1000;
            printf("detector time: %ld\n", total_time);

            cout << "Number of faces detected: " << dets.size() << endl;
            if (dets.empty()){
                return 0;
            }
            int l = dets[0].left() * raio;
            int t = dets[0].top() * raio;
            int r = dets[0].right()* raio;
            int b = dets[0].bottom() * raio;
            int x = (l + r)/2;
            int y = (t + b)/2;
            int xx = 0;
            if (x > edge/2){
                if (w - x > edge/2){
                    xx = x - edge/2;
                } else {
                    xx = w - edge;
                }
            }
            int yy = 0;
            if (y > edge/2){
                if (h - y > edge/2){
                    yy = y - edge/2;
                } else {
                    yy = h - edge;
                }
            }
            cv::Rect rect(xx, yy, edge, edge);
            cv::Mat dst = cvimg(rect);
            std::vector<int> compression_params;
            std::string suffix = ".png";
            compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
            compression_params.push_back(3);
            cv::imwrite("./imgs/dst2.png", dst, compression_params);
            return 0;
            // Now we show the image on the screen and the face detections as
            // red overlay boxes.
            /*win.clear_overlay();
            win.set_image(img);
            win.add_overlay(dets, rgb_pixel(255,0,0));

            cout << "Hit enter to process the next image..." << endl;
            cin.get();*/
        }
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}


