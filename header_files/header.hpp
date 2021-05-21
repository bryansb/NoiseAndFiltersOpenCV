#include <iostream>
#include <cstdlib>
#include <cstring>

#include <cmath>
#include <random>

#include <time.h>

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp> 
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp> 

using namespace std;
using namespace cv;

class Filter {
    private:
        int filter;
        int border;
        int kernelSize;
        int sigma;
    
    public:
        Filter();
        cv::Mat applyFilter(cv::Mat);
        void setFilter(int);
        void setBorder(int);
        void setSigma(int);
        void setkernelSize(int);
};

class Noise {
    private:
        int condiment;

    public:
        Noise();
        cv::Mat generateNoise(cv::Mat, double);
        void setCondiment(int);
};