#include "../header_files/header.hpp"

Filter::Filter(){
}

cv::Mat Filter::applyFilter(cv::Mat frame){
    cv::Mat filteredFrame = frame.clone();

    int kernel = this->kernelSizeFilter;
    double sigma = 0.3 * (((double) kernel - 1) * 0.5 - 1) + 0.8;

    if(kernel%2!=0 && kernel>0){

        switch (this->filter){
        case 0:
            // Retorna el mismo frame.
            break;

        case 1:
            medianBlur(frame, filteredFrame, kernel);
            break;

        case 2:
            GaussianBlur(frame, filteredFrame, Size(kernel, kernel), sigma, sigma);
            break;

        case 3:
            blur(frame, filteredFrame, Size(kernel, kernel), Point(-1, -1));
            break;
        
        default:
            break;
        }
        
    }
    
    return filteredFrame;
}

cv::Mat Filter::applyEdgeDetector(cv::Mat frame){
    cv::Mat edgeFrame = frame.clone();
    cv::Mat auxiliarFrame1;
    cv::Mat auxiliarFrame2;
    cv::Mat auxiliarFrame3;
    cv::Mat auxiliarFrame4;

    int kernel = this->kernelSizeEdge;
    int thres = this->threshold;
    int ratio = 3;
    int kernelCanny;

    if(kernel%2!=0 && kernel>0){

        switch (this->edge){
        case 0:
            if(kernel < 3){
                kernelCanny = 3;
            } else if(kernel > 7){
                kernelCanny = 7;  
            } else {
                kernelCanny = kernel;
            }
            
            Canny(frame, edgeFrame, thres, thres*ratio, kernelCanny);
            break;

        case 1:
            Laplacian(frame, auxiliarFrame1, CV_16S, kernel);
            convertScaleAbs(auxiliarFrame1, edgeFrame);
            break;

        case 2:
            Sobel(frame, auxiliarFrame1, CV_16S, 1, 0, kernel);
            Sobel(frame, auxiliarFrame2, CV_16S, 0, 1, kernel);
            convertScaleAbs(auxiliarFrame1, auxiliarFrame3);
            convertScaleAbs(auxiliarFrame2, auxiliarFrame4);
            addWeighted(auxiliarFrame3, 0.5, auxiliarFrame4, 0.5, 0, edgeFrame);
            break;
        
        default:
            break;
        }
    }
    
    return edgeFrame;   
}


void Filter::setFilter(int filter){
    this->filter = filter;
}

void Filter::setThreshold(int threshold){
    this->threshold = threshold;
}

void Filter::setkernelSizeFilter(int kernelSizeFilter){
    this->kernelSizeFilter = kernelSizeFilter;
}

void Filter::setkernelSizeEdge(int kernelSizeEdge){
    this->kernelSizeEdge = kernelSizeEdge;
}

void Filter::setEdgeDetector(int edge){
    this->edge = edge;
}