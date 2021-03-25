#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ManualGPIO.h"

#define FREQUENCY 0.25
#define TIME 5.0

enum{
  OUTPUT,
  INPUT,
};

int main(int argc, char const *argv[]) {
	if (argc != 5){
		printf("Usage: %s <output 1 pin number> <output 1 value> <output 2 pin number> <input pin number>\n", argv[0]);
		return 1;
	}

	int output1 = atoi(argv[1]);
  int value1 = atoi(argv[2]);
  int output2 = atoi(argv[3]);
	int input = atoi(argv[4]);
	int read = 0;
  double frequency = 0.25;
  double time = 5;

  printf("Setting pins %d and %d as outputs. Setting pin %d as input.\n", output1, output2, input);
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(input, INPUT);

	printf("Writing value %d to pin %d\n", value1, output1);
	digitalWrite(output1, value1);

  printf("Setting pin %d to blinking with frequency %f Hz for %f seconds\n", output2, frequency, time);
	blink(output2, FREQUENCY, TIME);

	printf("Reading from pin %d\n", input);
	for(int i = 0; i < 5; i++){
		read = digitalRead(input);
		printf("Value read on pin %d is %d\n", input, read);
    fflush(stdout);
		sleep(1);
	}

  printf("Releasing all pins\n");
  gpio_unexport(output1);
  gpio_unexport(output2);
	gpio_unexport(input);
	return 0;
}
