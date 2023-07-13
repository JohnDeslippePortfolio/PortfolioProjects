/* File Name: Graphics.c
* Author: John Deslippe 0754326
* Date: June 1st, 2022
* Platform toolset: Visual Studio 2022 V143
* Visual Studio Version: 17.1.6
* Compiler Version: Microsoft (R) C/C++ Optimizing COmpiler Version 19.31.31107
* Purpose: contains functions used to draw graphic elements
*/

#include "Graphics.h"
#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define HISTOGRAM_LENGTH 60 //defines the width of the histogram as a constan of 60 units wide


/* Function: DrawLine
*  Purpose: compares the values of 2 dereferenced pointers cast to double pointers, used in
*  Returns: void
*/

void DrawLine() {
	UINT lastCP = GetConsoleOutputCP();

	SetConsoleOutputCP(437);
	for (int i = 0; i <= 80; i++) {
		printf("\xCD");
	}
	SetConsoleOutputCP(lastCP);

	printf("\n");
}

/* Function: DrawHistogramTop
*  Purpose: Draws the top line of a histogram
*  Returns: void
*/

void DrawHistogramTop() {
	UINT lastCP = GetConsoleOutputCP(); //stores the users current codepage

	SetConsoleOutputCP(437); //changes the code page to 437
	for (int i = 0; i < 9; i++) {
		printf("\xC4");
	}
	printf(" \xDA");

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			printf("\xC4");
		}
		printf("\xC2");
	}
	printf("\n");

	SetConsoleOutputCP(lastCP); //restores user settings
}

/* Function: DrawHistogramBottom
*  Purpose: Draws the bottom line of a histogram
*  Returns: void
*/

DrawHistogramBottom() {
	UINT lastCP = GetConsoleOutputCP();//stores the users current codepage

	SetConsoleOutputCP(437); //changes the code page to 437
	for (int i = 0; i < 9; i++) {
		printf("\xC4");
	}
	printf(" \xC0");

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			printf("\xC4");
		}
		printf("\xC1");
	}
	printf("\n");

	SetConsoleOutputCP(lastCP); //restores user settings
}

/* Function: DrawHistogram
*  Purpose: Draws the top line of a histogram
*  Returns: void
*/

void DrawHistogram(int stats[], size_t length, size_t dataSize) {
	UINT lastCP = GetConsoleOutputCP();//stores the users designated codepage
	SetConsoleOutputCP(437);//manually assign the code page to 437
	double max = 0; //highest value in the stats passed through, used to determine the labels on the x axis of the histogram

	//find the highest value of the array passed
	for (size_t i = 0; i < length; i++) {
		if (stats[i] > max) //if the current element is greater than the current max, reassign max
			max = stats[i];
	}

	max = (max / dataSize) * 100; //convert max to a percentage

	//if max isn't a multiple of 5, rounds up to a nearby multiple of 5 
	if (fmod(max, 5.0) != 0) {
		if (fmod(max, 10) > 5)
			max += (10.0 - fmod(max, 10));
		else
			max += 5 - fmod(max, 10);

	}

	double labels[10]; //array to store the values of the 10 labels on the histogram

	//populate the labels arrays starting from the highest element, going down in decrments of 10%
	for (int i = 9; i > -1; i--) {
		labels[i] = max - ((max * 0.1) * (9 - i));
	}

	printf("Grp     %% 0");

	//displays the ten labels
	for (size_t i = 0; i < 10; i++) {
		printf("%6.1f", labels[i]);
	}
	printf("\n");

	DrawHistogramTop();
	for (size_t i = 0; i < 10; i++) {
		//display the bar label
		printf(" %c %5.2f%% \xF5", 'A' + i, ((double)stats[i] / dataSize) * 100);
		//histogram has a length of 60 spaces, therefore bars need to be relative to the max label, with a limit of 60
		int lineLength = ((((double)stats[i] / (double)dataSize) * 100)/max) * HISTOGRAM_LENGTH;
		for (int j = 0; j < lineLength; j++) {
			printf("\xDC");
		}
		printf("\n");
	}
	DrawHistogramBottom();

	SetConsoleOutputCP(lastCP);//resets the code page to the value it was set as initially
}

