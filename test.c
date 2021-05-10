#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "iostream"

int main() {
    // open the first webcam plugged in the computer
    CvCapture* capture=cvCreateCameraCapture(0);
    
    
    if(!capture)  //if no webcam detected or failed to capture anything
    {              // capture a frame 
    printf("exit\n");
        exit(0);
    }
	printf("pas exit\n");
	while (1){
		IplImage* img = cvQueryFrame( capture );          // retrieve the captured frame
		//IplImage* gris= cvQueryFrame( capture );
		//cvCvtColor(img, gris, CV_RGB2GRAY);
		cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
		//cvNamedWindow("GRIS", CV_WINDOW_AUTOSIZE);
		cvShowImage("Image", img);
		//cvShowImage("GRIS", gris);
		if (cvWaitKey(10)==27){
			break;
		}
	}
    cvReleaseCapture( &capture );
}
