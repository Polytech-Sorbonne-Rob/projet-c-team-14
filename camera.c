/*!
 * \file camera.c
 * \brief Fonctions permettant un mouvement du pan-tilt
 * \author Lucas RIBEIRO Léo LAVAL
 */
#include "camera.h"
/*!
 * \brief Macro pour changer l'incrementation d'angle.
 */
#define INCREM 1



/*!
 * \brief Permet au pan-tilt de mouvoir à partir des positions X et Y du centre d'une plage de couleur.
 *Elle modifie directement les angles dans le main.
 * \param[in] arduino Adresse des ports de l'arduino.
 * \param[in] X Position X.
 * \param[in] Y Position Y.
 * \param[out] q0 Angle Pan du pan-tilt.
 * \param[out] q1 Angle Tilt du pan-tilt.
 */

void moveCameraAuto(FILE * arduino, int X, int Y, int *q0, int *q1){

  if(X>=0 && Y>=0){
    if(*q1 < Q1MAX){
      if(X > MIDX+PREC || X < MIDX-PREC)
        X > MIDX ? (*q0)+= INCREM : (*q0)-=INCREM;
      if(Y > MIDY+PREC || Y < MIDY-PREC)
        Y > MIDY ? (*q1)+=INCREM : (*q1)-=INCREM;
    }else{
      if(X > MIDX+PREC || X < MIDX-PREC)
        X > MIDX ? (*q0)-=INCREM : (*q0)+=INCREM;
      if(Y > MIDY+PREC || Y < MIDY-PREC)
        Y > MIDY ? (*q1)+=INCREM : (*q1)-=INCREM;
    }

    if((*q0) < 0)
      (*q0) = 0;
    else if((*q0) > 180)
      (*q0) = 180;

    if((*q1) < 0)
      (*q1) = 0;
    else if((*q1) > 180)
      (*q1) = 180;

    fprintf(arduino, "%d %d\n", *q0, *q1);

    fflush(stdout);
  }
}



void moveCameraMan(FILE* arduino, int key,int *q0,int *q1){
  if(key == 1048698) // haut: touche z
    (*q1) += 3;
  else if(key == 1048691) // bas: touche s
    (*q1) -= 3;

  if(key == 1048676) // droite: touche d
    (*q0) += 3;
  else if(key == 1048689) // gauche: touche q
    (*q0) -= 3;

  if((*q0) < 0)
    (*q0) = 0;
  else if((*q0) > 180)
    (*q0) = 180;

  if((*q1) < 0)
    (*q1) = 0;
  else if((*q1) > 180)
    (*q1) = 180;

  fprintf(arduino, "%d %d\n", *q0, *q1);

  fflush(stdout);
}

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
