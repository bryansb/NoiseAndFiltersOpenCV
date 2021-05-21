#include "../header_files/header.hpp"

Filter::Filter(){
}

cv::Mat Filter::applyFilter(cv::Mat frame){
    cv::Mat filteredFrame = frame.clone();

    int size = this->kernelSize;
    double sigmaDecimal = ((double) this->sigma)/10.0;

    if(size%2!=0 && size>0){

        switch (this->filter){
        case 0:
            GaussianBlur(frame, filteredFrame, Size(size, size), sigmaDecimal, sigmaDecimal);
            break;

        case 1:
            medianBlur(frame, filteredFrame, size);
            break;

        case 2:
            blur(frame, filteredFrame, Size(size, size), Point(-1, -1), 1);
            break;
        
        default:
            break;
        }
        
    }
    
    return filteredFrame;
}

void Filter::setFilter(int filter){
    this->filter = filter;
}

void Filter::setBorder(int border){
    this->border = border;
}

void Filter::setSigma(int sigma){
    this->sigma = sigma;
}

void Filter::setkernelSize(int kernelSize){
    this->kernelSize = kernelSize;
}