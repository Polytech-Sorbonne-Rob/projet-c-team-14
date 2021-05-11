all:
	g++ -O2 -Wall -o test test.c -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -I/usr/include/opencv2

clean:
	rm -rf test
