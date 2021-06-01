#include "lecture.h"

char * lecture2string(char* sortie){
  system("tesseract ocr/capture.jpg ocr/texte --oem 1 --psm 7 -l foo+eng");
  FILE * lecture=fopen("ocr/output.txt","r");
  if(lecture == NULL){
    perror("Lecture impossible fichier output");
    exit(0);
  }
  fgets(sortie,100,lecture);
  printf("%s", sortie);
  fclose(lecture);
  return sortie;
}



void verif(char* gauche, char* droite){

}


int calcul(char *chaine){
  if(chaine[1] == '+')
    return (chaine[0]+chaine[2]);

  if(chaine[1] == '-')
    return (chaine[0]-chaine[2]);

  if(chaine[1] == 'x')
    return (chaine[0]*chaine[2]);

  return chaine[0];

  //perror("Pas de caractère de calcul");
  //printf("Chaine: %s", chaine);
  //exit(0);
}



void analyse(char* chaine){
  /*int caract_actu = 0;
  bool egal_trouve = false;

  char gauche[3], droite[3];


  caract_actu = 0;
  do{
    caract_actu = getchar(chaine);
    if()


  }while(caract_actu != '\0');
*/
}
