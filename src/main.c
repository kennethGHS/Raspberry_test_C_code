#include <unistd.h>
#include <stdio.h>
#include "ManualGPIO.h"

int main(int argc, char const *argv[]) {
	printf("Testing GPIO 3...");
	pinMode(3, 0);
	digitalWrite(3, 1);
	sleep(1);
	digitalWrite(3, 0);
	sleep(1);
	digitalWrite(3, 1);
	sleep(1);
	digitalWrite(3, 0);
	sleep(1);
	return 0;
}
