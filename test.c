#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "iostream"

//renvoie une image en noir et blanc avec le blanc corespondant à la couleur rouge
IplImage* transformation(IplImage * image){
	IplImage* imhsv = cvCreateImage( cvGetSize(image),8,3 );
	cvCvtColor(image,imhsv,CV_BGR2HSV);
	IplImage* noirblanc = cvCreateImage( cvGetSize(image),8,1 );
	cvInRangeS(imhsv, cvScalar(0,150,55),cvScalar(5,255,255), noirblanc);
	cvReleaseImage(&imhsv);
	return noirblanc;
}


int main() {
    // open the first webcam plugged in the computer
    CvCapture* capture=cvCaptureFromCAM(-1);
    
    
    if(!capture)  //if no webcam detected or failed to capture anything
    {              // capture a frame 
    printf("exit\n");
        exit(0);
    }
	printf("pas exit\n");
	while (1){
		IplImage* frame =cvQueryFrame( capture);
		IplImage* image = cvCreateImage( cvGetSize(frame),8,3 );
		
		
		image->origin =frame->origin;
		cvCopy(frame,image,0);
		
		IplImage* img=transformation(image);
		cvReleaseImage(&image);
		
		
		CvMoments* centre_couleur= (CvMoments*)malloc(sizeof(CvMoments));
		
		cvMoments(img, centre_couleur, 1);
		
		//on va checher les coordonnées du centre
		
		double moment_1 = cvGetSpatialMoment(centre_couleur,1,0);
		double moment_2 = cvGetSpatialMoment(centre_couleur,0,1);
		
		
		double aire = cvGetCentralMoment(centre_couleur,0,0);
		
		static int posX=0;
		static int posY=0;
		
		//int precX=posX;
		//int precY=posY;
		
		posX=moment_1/aire;
		posY=moment_2/aire;
		
		cvCircle(frame,cvPoint(posX,posY),5,cvScalar(0,100,100),-1);
		
		
		
		cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
		cvNamedWindow("GRIS", CV_WINDOW_AUTOSIZE);
		
		
		
		cvShowImage("Image", frame);
		cvShowImage("GRIS", img);
		
		delete centre_couleur;
		cvReleaseImage(&img);
		if (cvWaitKey(10)!=-1){
			cvDestroyWindow("GRIS");
			cvDestroyWindow("Image");
			cvReleaseCapture( &capture );
			return 0;
		}
		
		
		
	}
    
}
