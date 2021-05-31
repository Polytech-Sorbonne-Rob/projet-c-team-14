#include "camera.h"

#define INCREM 1
void moveCamera(FILE * camera, int X, int Y, int *q0, int *q1){

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

    fprintf(camera, "%d %d\n", *q0, *q1);

    fflush(stdout);
  }
}
