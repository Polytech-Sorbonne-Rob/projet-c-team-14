#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "iostream"
#include <unistd.h>

#include "camera.h"


// Variables globales
int lowH = 55;
int highH = 77;

int lowS = 88;
int highS = 201;

int lowV = 69;
int highV = 255;

//renvoie une image en noir et blanc avec le blanc corespondant à la couleur rouge
IplImage* transformation(IplImage * image){
	IplImage* imhsv = cvCreateImage( cvGetSize(image),8,3 );
	cvCvtColor(image,imhsv,CV_BGR2HSV);
	IplImage* noirblanc = cvCreateImage( cvGetSize(image),8,1 );
	cvInRangeS(imhsv, cvScalar(lowH,lowS,lowV),cvScalar(highH,highS,highV), noirblanc);
	cvReleaseImage(&imhsv);
	return noirblanc;
}

/*
void moveCamera(FILE * camera, int X, int Y, int *q0, int *q1){

  if(X>0 && Y>0){
    if(*q1 < Q1MAX){
      X > MIDX ? *q0++ : *q0--;
      Y > MIDY ? *q1++ : *q1--;
    }else{
      X > MIDX ? *q0-- : *q0++;
      Y > MIDY ? *q1++ : *q1--;
    }
    fprintf(camera, "%d %d\n", *q0, *q1);

    fflush(stdout);
  }
} */

int main() {

  FILE *camera = fopen("/dev/ttyACM0", "w"); // IL FAUT CONFIGURER CORRECTEMENT LA SORTIE ARDUINO
    // open the first webcam plugged in the computer
  CvCapture* capture=cvCaptureFromCAM(-1);

  int q1 = 45;
  int q0 = 90;
  fprintf(camera, "%d %d\n", q0, q1);

 if(!capture)  //if no webcam detected or failed to capture anything
    {              // capture a frame
    printf("exit\n");
        exit(0);
    }
	printf("pas exit\n");

    // TRACKBAR
    cvNamedWindow("Zone de detection");

    cvCreateTrackbar("Low H", "Zone de detection", &lowH, 255);
    cvCreateTrackbar("High H", "Zone de detection", &highH, 255);
    cvCreateTrackbar("Low S", "Zone de detection", &lowS, 255);
    cvCreateTrackbar("High S", "Zone de detection", &highS, 255);
    cvCreateTrackbar("Low V", "Zone de detection", &lowV, 255);
    cvCreateTrackbar("High V", "Zone de detection", &highV, 255);

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

		cvCircle(frame,cvPoint(posX,posY),5,cvScalar(0,0,255),-1);

		cvFlip(frame, frame, 1);
        cvFlip(img, img, 1);

		cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
		cvNamedWindow("GRIS", CV_WINDOW_AUTOSIZE);

        printf("X = %d  Y = %d\n", posX, posY);

if(posX>0 && posY>0){
    if(q1 < Q1MAX){
      posX > MIDX ? q0++ : q0--;
      posY > MIDY ? q1++ : q1--;
    }else{
      posX > MIDX ? q0-- : q0++;
      posY > MIDY ? q1++ : q1--;
    }
    fprintf(camera, "%d %d\n", q0, q1);

    fflush(stdout);
  }


		cvShowImage("Image", frame);
		cvShowImage("GRIS", img);

		delete centre_couleur;
		cvReleaseImage(&img);
		if (cvWaitKey(10)!=-1){
			cvDestroyWindow("GRIS");
			cvDestroyWindow("Image");
			cvReleaseCapture( &capture );
            fclose(camera);
			return 0;
		}
	}
}
