#include "opencv2/imgproc/types_c.h"
#include "traitement.h"
#define NOMFICHIER "output.txt"


IplImage * traitement(IplImage * image){
	IplImage* imhsv = cvCreateImage( cvGetSize(image),8,1 );
	cvCvtColor(image,imhsv,CV_BGR2GRAY);
	IplImage* noirblanc = cvCreateImage( cvGetSize(image),8,1 );
	cvAdaptiveThreshold(imhsv,noirblanc,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,21,5);
	cvReleaseImage(&imhsv);
	return noirblanc;
	
}

void deroule(IplImage * image){
	
	IplImage * gray=traitement(image);
	cvNamedWindow("calcul", CV_WINDOW_AUTOSIZE);
	
	cvRectangle(gray,cvPoint(80,100),cvPoint(600,300),cvScalar(0,255,255),1,1,0);
	cvShowImage("calcul", gray);
	
	cvSetImageROI(gray,cvRect(80,100,520,200));//on réduit la région d'intéret de l'image
	IplImage * rogne=cvCreateImage(cvGetSize(gray),8,1);
	cvCopy(gray, rogne,NULL);
	cvResetImageROI(gray);
	cvSaveImage("calcul.png",rogne);
	cvReleaseImage(&gray);
	
	if (cvWaitKey(5)==1048686){ // touche "p"
		cvDestroyWindow("calcul");
		
	}
	
}
