#include "camera.h"

void moveCamera(FILE * camera, int X, int Y, int *q0, int *q1){

  if(X>0 && Y>0){
    if(*q1 < Q1MAX){
      X > MIDX ? *q0++ : *q0--;
      Y > MIDY ? *q1++ : *q1--;
    }else{
      X > MIDX ? *q0-- : *q0++;
      Y > MIDY ? *q1++ : *q1--;
    }
    fprintf(camera, "%d %d\n", *q0, *q1);

    fflush(stdout);
  }
}
