#include "opencv2/opencv.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"
#include "opencv2/imgcodecs/imgcodecs_c.h"
#include "iostream"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "camera.h"

#include "camera.h"
#include "lecture.h"
#include <traitement.h>


// Variables globales
int lowH = 55;
int highH = 77;

int lowS = 88;
int highS = 201;

int lowV = 69;
int highV = 255;

static int posX=0;
static int posY=0;



//renvoie une image en noir et blanc avec le blanc corespondant à la couleur rouge
IplImage* transformation(IplImage * image){
	IplImage* imhsv = cvCreateImage( cvGetSize(image),8,3 );
	cvCvtColor(image,imhsv,CV_BGR2HSV);
	IplImage* noirblanc = cvCreateImage( cvGetSize(image),8,1 );
	cvInRangeS(imhsv, cvScalar(lowH,lowS,lowV),cvScalar(highH,highS,highV), noirblanc);
	cvReleaseImage(&imhsv);
	return noirblanc;
}


int main() {
  system("stty 9600"); // met le terminal en 9600 baud
  FILE *arduino = fopen("/dev/ttyACM0", "w"); // IL FAUT CONFIGURER CORRECTEMENT LA SORTIE ARDUINO
  if(arduino == NULL){
    perror("ARDUINO OFF");
    exit(0);
  }

  // open the first webcam plugged in the computer
  CvCapture* capture=cvCaptureFromCAM(-1);

  if(!capture)  //if no webcam detected or failed to capture anything
    {              // capture a frame
      perror("CAMERA OFF");
      exit(0);
    }


  bool control_kb = true;
	int mode=1;
  int q1 = 30;
  int q0 = 90;
  fprintf(arduino, "%d %d\n", q0, q1);

  // TRACKBAR
  cvNamedWindow("Zone de detection");

  cvCreateTrackbar("Low H", "Zone de detection", &lowH, 255);
  cvCreateTrackbar("High H", "Zone de detection", &highH, 255);
  cvCreateTrackbar("Low S", "Zone de detection", &lowS, 255);
  cvCreateTrackbar("High S", "Zone de detection", &highS, 255);
  cvCreateTrackbar("Low V", "Zone de detection", &lowV, 255);
  cvCreateTrackbar("High V", "Zone de detection", &highV, 255);


  // BOUCLE CAPTURE
  while (1){
    int key = cvWaitKey(10);
    IplImage* frame =cvQueryFrame( capture);
    IplImage* image = cvCreateImage( cvGetSize(frame),8,3 );
    
    if(key == 1048694) //  touche v
		mode=1;//TRACKING
    if(key == 1048673) //  touche b
		mode=2;//CALCUL
    
    switch(mode){

		case(1) : {
			image->origin =frame->origin;
			cvCopy(frame,image,0);

			IplImage* img=transformation(image);
			cvReleaseImage(&image);


			CvMoments* centre_couleur= (CvMoments*)malloc(sizeof(CvMoments));

			cvMoments(img, centre_couleur, 1);

			//on va checher les coordonnées du centre

			if(!control_kb){
			  double moment_1 = cvGetSpatialMoment(centre_couleur,1,0);
			  double moment_2 = cvGetSpatialMoment(centre_couleur,0,1);

			  double aire = cvGetCentralMoment(centre_couleur,0,0);

			  posX=moment_1/aire;
			  posY=moment_2/aire;

			  cvCircle(frame,cvPoint(posX,posY),5,cvScalar(0,0,255),-1);
			}
			cvFlip(frame, frame, 1);
			cvFlip(img, img, 1);

			cvNamedWindow( "Image", CV_WINDOW_AUTOSIZE );
			cvNamedWindow("GRIS", CV_WINDOW_AUTOSIZE);

			printf("X = %d  Y = %d\n", posX, posY);


			if(key == 1048697) //touche y
			  moveYes(arduino);

			if(key == 1048686) //touche n
			  moveNo(arduino);

			// TRACKING
			if(key ==1048685) // touche m
			  control_kb = !control_kb;

			// tracking manuel
			if(control_kb){

			  //printf("%d", key);

			  if(key == 1048698) // haut: touche z
				q1 += 3;
			  else if(key == 1048691) // bas: touche s
				q1 -= 3;

			  if(key == 1048676) // droite: touche d
				q0 += 3;
			  else if(key == 1048689) // gauche: touche q
				q0 -= 3;

			  if(q0 < 0)
				q0 = 0;
			  else if(q0 > 180)
				q0 = 180;

			  if(q1 < 0)
				q1 = 0;
			  else if(q1 > 180)
				q1 = 180;

			  fprintf(arduino, "%d %d\n", q0, q1);

			  fflush(stdout);


			}
			
			else //tracking auto
			  moveCamera(arduino, posX, posY, &q0, &q1);

			cvShowImage("Image", frame);
			cvShowImage("GRIS", img);

			delete centre_couleur;
			cvReleaseImage(&img);
			break;
		}
    	
		case(2):{
			
			
			break;
		}
    }
    	
    	
    if (key==1048603){ // touche "echap"
      cvDestroyWindow("GRIS");
      cvDestroyWindow("Image");
      cvReleaseCapture( &capture );
      fclose(arduino);
      return 0;
    }
  }
}
