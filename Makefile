# options de compilation
CC = g++
CCFLAGS = -Wall -g
LIBSDIR = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -I/usr/include/opencv2 -lopencv_imgcodecs
LDFLAGS =

# fichiers du projet
SRC = main.c camera.c lecture.c traitement.c
OBJ = $(SRC:.c=.o)
EXEC = main

# règle initiale
all : $(EXEC)

# dépendance des .h
traitement.o: traitement.h
lecture.o: lecture.h
camera.o: camera.h
main.o: camera.h lecture.h traitement.h


# règles de compilation
%.o:%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

#règle d'édition de liens
$(EXEC) :$(OBJ)
	$(CC) -g -o $@ $^ $(LIBSDIR) $(LDFLAGS)

#règles suplémentaires
doxy :
	doxygen Doxyfile

clean :
	rm -f *.o $(EXEC) *.png *.txt
