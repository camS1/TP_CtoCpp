all:ppm
ppm: ppm.c functionpicture.o
	gcc -o ppm ppm.c functionpicture.o
functionpicture.o:  functionpicture.h functionpicture.c
	gcc -o functionpicture.o  functionpicture.c -c

