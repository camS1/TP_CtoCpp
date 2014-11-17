all:ppm
ppm: ppm.c functionpicture.o
	g++ -o ppm ppm.c functionpicture.o
functionpicture.o:  functionpicture.h functionpicture.c
	g++ -o functionpicture.o  functionpicture.c -c

