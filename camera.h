#ifndef CAMERA_H

#include <unistd.h>
#include "iostream"

#define MIDX 320
#define MIDY 240
#define PREC 25

#define Q1MAX 91

void moveCameraAuto(FILE* arduino,int X, int Y, int *q0, int *q1);
void moveCameraMan(FILE* arduino, int key);

void moveYes(FILE* arduino);
void moveNo(FILE* arduino);
#endif
