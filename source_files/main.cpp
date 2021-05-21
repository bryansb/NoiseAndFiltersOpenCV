#include "../header_files/header.hpp"

cv::Mat frame;
cv::Mat grayFrame;
cv::Mat noisyFrame;
cv::Mat filteredFrame;

cv::Mat pepperFrame;
cv::Mat saltFrame;

int pepperPorcentage = 0;
int saltPorcentage = 0;

int MAX_NOISE = 100;

Noise pepperNoise;
Noise saltNoise;
// Filter filter;

void pepperNoiseTrackbar(int v, void *data){
    pepperFrame = pepperNoise.generateNoise(grayFrame, pepperPorcentage);
    //cout << pepperPorcentage << endl;
}

void saltNoiseTrackbar(int v, void *data){
    saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);
    //cout << pepperPorcentage << endl;
}

int main(int, char**) {
    srand(time(NULL));

    pepperNoise.setCondiment(0);
    saltNoise.setCondiment(255);

    VideoCapture video(0);

    if(video.isOpened()){
        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("Video con Ruido", WINDOW_AUTOSIZE);
        //namedWindow("Video con Filtros", WINDOW_AUTOSIZE);
        
        //
        createTrackbar("Pepper", "Video Original", &pepperPorcentage, MAX_NOISE, pepperNoiseTrackbar, NULL);
        createTrackbar("Salt", "Video Original", &saltPorcentage, MAX_NOISE, saltNoiseTrackbar, NULL);

        while(3==3){
            video >> frame;
            flip(frame, frame, 1);
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

            if(noisyFrame.empty()){
                noisyFrame = grayFrame.clone();
            } else {
               pepperFrame = pepperNoise.generateNoise(grayFrame, pepperPorcentage);
               saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);

               //bitwise_and(pepperFrame, saltFrame, noisyFrame);
               noisyFrame = pepperFrame + saltFrame;
            }

            

            imshow("Video Original", grayFrame);
            imshow("Video con Ruido", noisyFrame);
            //imshow("Video con Filtros", newFrame);

            //setMouseCallback("Video Nuevo", onMouseCallback, NULL);


            if(waitKey(23) == 27){
                break;
            }
        }

        video.release();
    }

    waitKey(0); 
    destroyAllWindows();
    return 0;
}
