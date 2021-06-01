#include "opencv2/imgproc/types_c.h"
#include "traitement.h"
#define NOMFICHIER "output.txt"

//suprime les espaces d'une chaine de caractère
void suprEspace(char *Phrase, char *NewPhrase){
    int i, j = 0;

    for(i=0;i<100;i++){
        if(Phrase[i]!=' ')
        {
           NewPhrase[j++] = Phrase[i];
        }
    }
}

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
	
	if (cvWaitKey(5)==1048586){// touche enter
		cvSaveImage("calcul.png",rogne);
		system("tesseract calcul.png output --oem 1 --psm 7 -l foo+eng");
		FILE * lecture=fopen("output.txt","r");
		  if(lecture == NULL){
			perror("Lecture impossible fichier output");
			exit(0);
		  }
		char * acespace=(char*)malloc(sizeof(char)*100);
		fgets(acespace,100,lecture);
		char * sortie=(char*)malloc(sizeof(char)*100);
		suprEspace(acespace,sortie);
		free(acespace);
  		
		printf("la suite est :%s\nreprendre photo : a, continuer: z\n",sortie);
		fclose(lecture);
		int key;
		do{
			key=cvWaitKey(0);
		}while(key==1048586 && (key==1048673 || key == 1048698));//touche enter
		
		if(key==1048673){// touche a
			
			deroule(image);
		}
		if(key == 1048698){ // touche z
			
		}
		free(sortie);
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&rogne);
	
	if (cvWaitKey(5)==1048686){ // touche "p"
		cvDestroyWindow("calcul");
		
	}
	
}
