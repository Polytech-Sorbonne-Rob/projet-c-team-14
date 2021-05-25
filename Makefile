# options de compilation
CC = g++
CCFLAGS = -Wall -g
LIBSDIR = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -I/usr/include/opencv2
LDFLAGS =

# fichiers du projet
SRC = test.c camera.c
OBJ = $(SRC:.c=.o)
EXEC = main

# règle initiale
all : $(EXEC)

# dépendance des .h
camera.o: camera.h
main.o: camera.h


# règles de compilation
%.o:%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

#règle d'édition de liens
$(EXEC) :$(OBJ)
	$(CC) -g -o $@ $^ $(LIBSDIR) $(LDFLAGS)

#règles suplémentaires
clean :
	rm -f *.o $(EXEC)
