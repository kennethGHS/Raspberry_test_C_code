CC = gcc
SOURCE = ./src/main.c ./lib/ManualGPIO.c  ./lib/Monitoring.c
LIB = -lpigpio -lrt
build:
	gcc -o testeo $(SOURCE) -Wall -pthread $(LIB)

