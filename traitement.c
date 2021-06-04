#include "opencv2/imgproc/types_c.h"
#include "traitement.h"
#include "lecture.h"
#define NOMFICHIER "output.txt"



/*!
 * \brief Suprime les espaces d'une chaine de caractère
 * \param[out] Phrase chaine avec espaces
 * \param[out] NewPhrase chaine avec espaces suprimés
 */

void suprEspace(char *Phrase, char *NewPhrase){
    int i, j = 0;

    for(i=0;i<100;i++){
        if(Phrase[i]!=' ')
        {
           NewPhrase[j++] = Phrase[i];
        }
    }
}

/*!
 * \brief Transforme un image en une image binarisée en noir et Blanc
 * \param[out] image image à binariser
 */
IplImage * traitement(IplImage * image){
	IplImage* imhsv = cvCreateImage( cvGetSize(image),8,1 );
	cvCvtColor(image,imhsv,CV_BGR2GRAY);
	IplImage* noirblanc = cvCreateImage( cvGetSize(image),8,1 );
	cvAdaptiveThreshold(imhsv,noirblanc,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,21,5);
	cvReleaseImage(&imhsv);
	return noirblanc;
	
}


/*!
 * \brief Permet de lire un suite de caractère manuscrit grâce à la caméra
 la caméra fait un signe oui si l'équation inscrite est correcte et un signe non si elle ne l'est pas
 * \param[out] image image prise par la camera
 */
void deroule(IplImage * image){
	
	//on créer une fenêtre avec un rectangle dedans
	IplImage * gray=traitement(image);
	cvNamedWindow("calcul", CV_WINDOW_AUTOSIZE);
	
	cvRectangle(gray,cvPoint(80,100),cvPoint(600,300),cvScalar(0,255,255),1,1,0);
	cvShowImage("calcul", gray);
	
	//on réduit la région d'intéret de l'image pour la rogner
	cvSetImageROI(gray,cvRect(80,100,520,200));
	IplImage * rogne=cvCreateImage(cvGetSize(gray),8,1);
	cvCopy(gray, rogne,NULL);
	cvResetImageROI(gray);
	
	//prise de la photo : on enregistre l'image et on utilise tesseract pour la lire
	if (cvWaitKey(5)==1048586){ // touche enter
		cvSaveImage("calcul.png",rogne);
		system("tesseract calcul.png output --oem 1 --psm 7 -l foo+eng");
		FILE * lecture=fopen("output.txt","r");
		
		if(lecture == NULL){
			perror("Lecture impossible fichier output");
			exit(0);
		}
		
		//on suprime les espaces de la chaine (erreur que l'on a rencontré plusieurs fois)
		char * acespace=(char*)malloc(sizeof(char)*100);
		fgets(acespace,100,lecture);
		char * sortie=(char*)malloc(sizeof(char)*100);
		suprEspace(acespace,sortie);
		free(acespace);
  		
  		//affichage de l'equation pour une eventuelle prise d'une autre photo
		printf("la suite est :%s\nreprendre photo : z, continuer: a\n",sortie);
		fclose(lecture);
		int key;
		//touche touche a ou z enfoncée 
		do{
			key=cvWaitKey(0);
		}while(key==1048673 || key == 1048698);
		
		if(key==1048673){// touche a
			analyse(sortie);
			
		}
		
		free(sortie);
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&rogne);
	
}
