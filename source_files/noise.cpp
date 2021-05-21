#include "../header_files/header.hpp"

Noise::Noise(){
}

cv::Mat Noise::generateNoise(cv::Mat frame, double percentage = 25){
    cv::Mat noisyFrame = frame.clone();
    percentage = percentage / 100;

    //cout << "Pepper: " << percentage << endl;

    double frameRows = frame.rows;
    double frameCols = frame.cols;

    int total = (int) (percentage * frameRows * frameCols);

    int count = 0;
    int row = 0;
    int col = 0;

    while (count < total){
        row = rand() % frame.rows;
        col = rand() % frame.cols;

        noisyFrame.at<uchar>(row, col) = this->condiment;

        count++;
    }

    return noisyFrame;
}

void Noise::setCondiment(int condiment){
    this->condiment = condiment;
}