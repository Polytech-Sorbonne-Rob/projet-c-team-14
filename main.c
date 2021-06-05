/*!
 * \file main.c
 * \brief Les variables sont utilisés pour régler la couleur (en HSV). Ici les paramètres correspondent à une plage de couleurs vertes.
 * La fonction utilise ces variables globales afin de traiter l'image en noir et blanc, et afficher en blanc uniquement la plage de couleurs correspondante.
 */


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
#include "lecture.h"
#include "traitement.h"



// Variables globales

int lowH = 55;
int highH = 77;

int lowS = 88;
int highS = 201;

int lowV = 69;
int highV = 255;

static int posX=0;
static int posY=0;


/*!
 * \brief Renvoie une image en noir et blanc avec le blanc corespondant à la couleur verte.
 * \param[in] image image à modifier
 */

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
  int mode=2;
  int q1 = 30;
  int q0 = 90;
  fprintf(arduino, "%d %d\n", q0, q1);


  // BOUCLE CAPTURE
  while (1){

    int key = cvWaitKey(10);
    IplImage* frame =cvQueryFrame(capture);
    IplImage* image = cvCreateImage( cvGetSize(frame),8,3 );

    if(key == 1048694) {//  touche v
		mode=1;//TRACKING
		cvDestroyAllWindows();
	}
    if(key == 1048674){ //  touche b
		mode=2;//CALCUL
		cvDestroyAllWindows();
	}

    switch(mode){

		case(1) : {
			// TRACKBAR
          cvNamedWindow("Zone de detection", CV_WINDOW_FREERATIO);
          cvMoveWindow("Zone de detection", 0, 600);
		  	cvCreateTrackbar("Low H", "Zone de detection", &lowH, 255);
			cvCreateTrackbar("High H", "Zone de detection", &highH, 255);
			cvCreateTrackbar("Low S", "Zone de detection", &lowS, 255);
			cvCreateTrackbar("High S", "Zone de detection", &highS, 255);
			cvCreateTrackbar("Low V", "Zone de detection", &lowV, 255);
			cvCreateTrackbar("High V", "Zone de detection", &highV, 255);
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
            cvMoveWindow("Image", 0, 0);
			cvNamedWindow("GRIS", CV_WINDOW_AUTOSIZE);
            cvMoveWindow("GRIS", 750, 0);

			printf("X = %d  Y = %d\n", posX, posY);


		// forcer mouvement predef

			if(key == 1048697) //touche y
			  moveYes(arduino);

			if(key == 1048686) //touche n
			  moveNo(arduino);

			// TRACKING
			if(key ==1048685) // touche m
			  control_kb = !control_kb; // control clavier ou non


		// tracking manuel
			if(control_kb){
				moveCameraMan(arduino, key, &q0, &q1);
			}
		//tracking auto
			else
			  moveCameraAuto(arduino, posX, posY, &q0, &q1);

			cvShowImage("Image", frame);
			cvShowImage("GRIS", img);

			delete centre_couleur;
			cvReleaseImage(&img);
			break;
		}

		case(2):{

			moveCameraMan(arduino, key, &q0, &q1);
			image->origin =frame->origin;
			cvCopy(frame,image,0);
            //cvFlip(image, image, 0);
			deroule(image, arduino);

			break;
		}
    }



    if (key==1048603){ // touche "echap"
      cvDestroyAllWindows();
      cvReleaseCapture( &capture );
      fclose(arduino);
      return 0;
    }
  }
}
