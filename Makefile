CC = gcc
SOURCE = main.c ./Code/IOManagement.c
LIB = -lpigpio -lrt
build:
	gcc -o testeo $(SOURCE) -Wall -pthread $(LIB)

