#include "../header_files/header.hpp"

cv::Mat frame;
cv::Mat grayFrame;
cv::Mat noisyFrame;
cv::Mat filteredFrame;
cv::Mat edgeFrame;

cv::Mat pepperFrame;
cv::Mat saltFrame;

int pepperPorcentage = 0;
int saltPorcentage = 0;
int MAX_NOISE = 100;

int filterNumber = 0;
int edgeNumber = 0;
int thres = 40;
int kernelSizeF = 3;
int kernelSizeE = 3; 
int MAX_KERNEL_SIZE = 17;
int MAX_KERNEL_SIZE_EDGE = 7;
int MAX_THRES_VALUE = 150;
int MAX_FILTER_NUMBER = 3;
int MAX_EDGE_NUMBER = 2;

Noise pepperNoise;
Noise saltNoise;
Filter filter;

void pepperNoiseTrackbar(int v, void *data){
    pepperFrame = pepperNoise.generateNoise(grayFrame, pepperPorcentage);
}

void saltNoiseTrackbar(int v, void *data){
    saltFrame = saltNoise.generateNoise(grayFrame, saltPorcentage);
}

void changeKernelFilterSize(int v, void *data){
    filter.setkernelSizeFilter(kernelSizeF);
}

void changeKernelEdgeSize(int v, void *data){
    filter.setkernelSizeEdge(kernelSizeE);
}

void changeFilter(int v, void *data){
    filter.setFilter(filterNumber);
}

void changeEdgeDetector(int v, void *data){
    filter.setEdgeDetector(edgeNumber);
}

void changeThreshold(int v, void *data){
    filter.setThreshold(thres);
}

void deleteVariables(){
    delete &frame;
    delete &grayFrame;
    delete &noisyFrame;
    delete &filteredFrame;
    delete &edgeFrame;
    delete &pepperFrame;
    delete &saltFrame;
    delete &pepperPorcentage;
    delete &saltPorcentage;
    delete &MAX_NOISE;
    delete &filterNumber;
    delete &kernelSizeF; 
    delete &MAX_KERNEL_SIZE;
    delete &MAX_FILTER_NUMBER;
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
        namedWindow("Video con Bordes", WINDOW_AUTOSIZE);
        
        // ----- Trackbars
        // --- Para el ruido
        createTrackbar("Pepper %", "Video con Ruido", &pepperPorcentage, MAX_NOISE, pepperNoiseTrackbar, NULL);
        createTrackbar("Salt %", "Video con Ruido", &saltPorcentage, MAX_NOISE, saltNoiseTrackbar, NULL);
        
        // --- Para el filtrado
        createTrackbar("Filter", "Video con Filtros", &filterNumber, MAX_FILTER_NUMBER, changeFilter, NULL);
        createTrackbar("Kernel", "Video con Filtros", &kernelSizeF, MAX_KERNEL_SIZE, changeKernelFilterSize, NULL);

        // --- Para la detección de bordes
        createTrackbar("Edge-D", "Video con Bordes", &edgeNumber, MAX_EDGE_NUMBER, changeEdgeDetector, NULL);
        createTrackbar("Kernel", "Video con Bordes", &kernelSizeE, MAX_KERNEL_SIZE_EDGE, changeKernelEdgeSize, NULL);
        createTrackbar("Thres (C)", "Video con Bordes", &thres, MAX_THRES_VALUE, changeThreshold, NULL);

        filter.setkernelSizeEdge(3);
        filter.setkernelSizeFilter(3);

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
                cv::addWeighted(pepperFrame, 0.5, saltFrame, 0.5, 0, noisyFrame);
            }
            
            // --- Aplicación de Filtros
            if(filteredFrame.empty()){
                filteredFrame = noisyFrame.clone();
                edgeFrame = filter.applyEdgeDetector(filteredFrame);
            } else {
                filteredFrame = filter.applyFilter(noisyFrame);
                edgeFrame = filter.applyEdgeDetector(filteredFrame);
            }

            // --- Mostrar videos
            imshow("Video Original", grayFrame);
            imshow("Video con Ruido", noisyFrame);
            imshow("Video con Filtros", filteredFrame);
            imshow("Video con Bordes", edgeFrame);

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
