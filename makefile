all:ppm
ppm: ppm.cpp functionpicture.o
	g++ -o ppm ppm.cpp functionpicture.o
functionpicture.o:  functionpicture.h functionpicture.cpp
	g++ -o functionpicture.o  functionpicture.cpp -c

