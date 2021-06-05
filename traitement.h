#ifndef TRAITEMENT_H
#include "opencv2/videoio/videoio_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"
#include "opencv2/imgcodecs/imgcodecs_c.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
IplImage * traitement(IplImage * image);
void deroule(IplImage * image, FILE* arduino);
void suprEspace(char *expr, char *res);

#endif
