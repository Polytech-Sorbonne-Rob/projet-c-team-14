/*!
 * \file traitement.c
 * \brief Fonctions permettant de traiter une chaîne de caractères, de binariser un image, et de faire tourner le logiciel tesseract.
 */


#include "opencv2/imgproc/types_c.h"
#include "traitement.h"
#include "lecture.h"
#define NOMFICHIER "output.txt"



static int blockSize = 10, constante = 13;

/*!
 * \brief Permet de lire un suite de caractère manuscrit grâce à la caméra.
 * La caméra fait un signe oui si l'équation inscrite est correcte et un signe non si elle ne l'est pas.
 * \param[in] image Image prise par la camera.
 */
void deroule(IplImage * image, FILE * arduino){
	//on créer une fenêtre avec un rectangle dedans
  int blockSizeFixed = 2*blockSize+3;
  IplImage * gray=traitement(image,blockSizeFixed,constante);
	cvNamedWindow("calcul", CV_WINDOW_AUTOSIZE);

	cvRectangle(gray,cvPoint(80,100),cvPoint(600,300),cvScalar(0,255,255),1,1,0);
	cvShowImage("calcul", gray);
    cvCreateTrackbar("BlockSize", "calcul", &blockSize, 50);
    cvCreateTrackbar("Constant", "calcul", &constante, 50);

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
		printf("la suite est :%s\nreprendre photo : e, continuer: a\n",sortie);
		fclose(lecture);
		int key;
		//touche touche a ou e enfoncée
		do{
          //printf("ok\n");
			key=cvWaitKey(0);
            //printf("ou\n");
		}while((key!=1048673) && (key!=1048677));

		if(key==1048673){// touche a
          printf("Analyse...\n");
          analyse(sortie, arduino);
		}

        if(key==1048677){
          printf("Appuyer sur entrée pour capturer.\n");
        }

		free(sortie);
	}
	cvReleaseImage(&gray);
	cvReleaseImage(&rogne);
}


/*!
 * \brief Supprime les espaces d'une chaîne de caractères.
 * \param[in] Phrase Chaîne avec espaces.
 * \param[out] NewPhrase Chaine avec espaces supprimés.
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
 * \brief Retourne une image en une image binarisée en noir et blanc.
 * \param[in] image Image à binariser.
 * \param[in] blockSize Paramètre pour régler l'épaisseur des contours.
 * \param[in] constante Paramètre pour régler le bruit de l'image.
 */
IplImage * traitement(IplImage * image, int blockSize, int constante){
	IplImage* imhsv = cvCreateImage( cvGetSize(image),8,1 );
	cvCvtColor(image,imhsv,CV_BGR2GRAY);
	IplImage* noirblanc = cvCreateImage( cvGetSize(image),8,1 );
	cvAdaptiveThreshold(imhsv,noirblanc,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,blockSize,constante);
	cvReleaseImage(&imhsv);
	return noirblanc;

}


