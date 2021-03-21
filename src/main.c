#include <unistd.h>
#include <stdio.h>
#include "ManualGPIO.h"

int main(int argc, char const *argv[]) {
	printf("Testing GPIO 2...\n");
	pinMode(2, 0);
	digitalWrite(2, 1);
	sleep(1);
	digitalWrite(2, 0);
	sleep(1);
	digitalWrite(2, 1);
	sleep(1);
	digitalWrite(2, 0);
	sleep(1);
	return 0;
}
