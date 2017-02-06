#include <wiringPi.h>
#include <mcp23017.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_EXPANDERS 1
#define EXPANDER_1_ADDR 0x20


FILE *statusFile;


int main(void) {
	wiringPiSetup();

	// Expander #1 got pins range 65 - 80
	// ie. GPA0 = 65, GPA1 = 66 ... GPA7 = 72
	// GPB0 = 73, GPB1 = 74 ... GPB7 = 80.
	// Expander #2 got pins  range 81 - 96
	// ie. GPA0 = 81, GPA1 = 82 ... GPA7 = 88
	// GPB0 = 89, GPB1 = 90 ... GPB7 = 96
	mcp23017Setup(65, EXPANDER_1_ADDR);

	int i = 0;

	for (i = 65; i <= 80; i++) {
		pinMode(i, INPUT);
		
		//Since  MCP23017 only has pull up resistors
		//you have to manually connect every pin
		//to GND with +4.7kOhm resistor.
		//pullUpDnControl(i, PUD_DOWN);
	}

	statusFile = fopen("./pinStatus.txt", "w+");

	if (!statusFile) {
		printf("Error opening file... Bye, bye!\n");
		return 1;
	}

	for (i = 65; i <= 80; i++) {
		// For text file PINS would be counted 1-16 for Expander #1
		// 17-32 for Expander #2 etc...
		fprintf(statusFile, "pin%d %d\n", i - 64, digitalRead(i));
		
		printf("read pin%d, state: %d\n", i - 64, digitalRead(i));
	}

	printf("Updating statuses done... Exiting...\n");

	fclose(statusFile);

	return 0;
}
