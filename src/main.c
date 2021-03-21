#include <unistd.h>
#include <stdio.h>
#include "ManualGPIO.h"

int main(int argc, char const *argv[]) {
	if (argc != 2){
		printf("Usage: %s <pin number>\n");
		return 1;
	}
	int pin = atoi(argv[1]);
	printf("Testing GPIO %d...\n", pin);
	pinMode(pin, 0);
	digitalWrite(pin, 1);
	sleep(1);
	digitalWrite(pin, 0);
	sleep(1);
	blink(pin, 0.5, 10);
	return 0;
}
