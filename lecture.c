#include "lecture.h"

void moveYes(FILE * arduino){
  for(int i = 0; i < 70; i++){
    fprintf(arduino, "90 %d\n", i);
    fflush(stdout);
  }
  for(int i = 70; i > 0; i--){
    fprintf(arduino, "90 %d\n", i);
    fflush(stdout);
  }
}

void moveNo(FILE * arduino){
  for(int i = 45; i < 135; i++){
    fprintf(arduino, "%d 15\n", i);
    fflush(stdout);
  }
  for(int i = 135; i > 45; i--){
    fprintf(arduino, "%d 15\n", i);
    fflush(stdout);
  }
}


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
