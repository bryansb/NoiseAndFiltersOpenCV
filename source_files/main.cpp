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

int filterNumber = 0;
int kernelSize = 1; 
int sigma = 1;
int MAX_SIGMA = 70;
int MAX_KERNEL = 255;
int MAX_FILTER = 2;

Noise pepperNoise;
Noise saltNoise;
Filter filter;

void pepperNoiseTrackbar(int v, void *data){
    pepperFrame = pepperNoise.generateNoise(grayFrame, pepperPorcentage);
}

void saltNoiseTrackbar(int v, void *data){
    saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);
}

void changeKernelSize(int v, void *data){
    // saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);
    filter.setkernelSize(kernelSize);
}

void changeSigma(int v, void *data){
    // saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);
    filter.setSigma(sigma);
}

void changeFilter(int v, void *data){
    // saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);
    filter.setFilter(filterNumber);
}

void deleteVariables(){
    delete &frame;
    delete &grayFrame;
    delete &noisyFrame;
    delete &filteredFrame;
    delete &pepperFrame;
    delete &saltFrame;
    delete &pepperPorcentage;
    delete &saltPorcentage;
    delete &MAX_NOISE;
    delete &filterNumber;
    delete &kernelSize; 
    delete &sigma;
    delete &MAX_SIGMA;
    delete &MAX_KERNEL;
    delete &MAX_FILTER;
    delete &pepperNoise;
    delete &saltNoise;
    delete &filter;
}

int main(int, char**) {
    srand(time(NULL));

    pepperNoise.setCondiment(0);
    saltNoise.setCondiment(255);

    VideoCapture video(0);

    if(video.isOpened()){

        // --- Iniciar ventanas
        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("Video con Ruido", WINDOW_AUTOSIZE);
        namedWindow("Video con Filtros", WINDOW_AUTOSIZE);
        
        // ----- Trackbars
        // --- Para el ruido
        createTrackbar("Pepper %", "Video con Ruido", &pepperPorcentage, MAX_NOISE, pepperNoiseTrackbar, NULL);
        createTrackbar("Salt %", "Video con Ruido", &saltPorcentage, MAX_NOISE, saltNoiseTrackbar, NULL);
        
        // --- Para el filtrado
        createTrackbar("Filter", "Video con Filtros", &filterNumber, MAX_FILTER, changeFilter, NULL);
        createTrackbar("Kernel", "Video con Filtros", &kernelSize, MAX_KERNEL, changeKernelSize, NULL);
        createTrackbar("Sigma", "Video con Filtros", &sigma, MAX_SIGMA, changeSigma, NULL);

        while(3==3){
            video >> frame;
            flip(frame, frame, 1);
            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

            // --- Generación de Ruido
            if(noisyFrame.empty()){
                noisyFrame = grayFrame.clone();
            } else {
               pepperFrame = pepperNoise.generateNoise(grayFrame, pepperPorcentage);
               saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);

               //noisyFrame = cv::abs(pepperFrame + saltFrame);
               //cv::add(pepperFrame, saltFrame, noisyFrame);
               cv::addWeighted(pepperFrame, 0.5, saltFrame, 0.5, 0, noisyFrame);
            }
            
            if(filteredFrame.empty()){
                filteredFrame = noisyFrame.clone();
            } else {
               filteredFrame = filter.applyFilter(noisyFrame);
            }

            // --- Mostrar videos
            imshow("Video Original", grayFrame);
            imshow("Video con Ruido", noisyFrame);
            imshow("Video con Filtros", filteredFrame);

            //setMouseCallback("Video Nuevo", onMouseCallback, NULL);
            if(waitKey(23) == 27){
                break;
            }
        }

        video.release();
    }

    waitKey(0); 
    destroyAllWindows();
    deleteVariables();
    return 0;
}
