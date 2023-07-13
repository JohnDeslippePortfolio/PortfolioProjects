/* File Name: Project2Statistics.c
* Author: John Deslippe 0754326
* Date: June 1st, 2022
* Platform toolset: Visual Studio 2022 V143
* Visual Studio Version: 17.1.6
* Compiler Version: Microsoft (R) C/C++ Optimizing COmpiler Version 19.31.31107
* Purpose: Reads the users input, through either a file, as specificied as a an argument, or through a series of keyboard inputs terminated with 'end' or EOF
*			Sorts the input, then returns statistics based off of the sorted input
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <Windows.h>
#include <math.h>
#include "Graphics.h"
#include "JDStatistics.h"

#define MAX_LINE 1000 //defines the max length of a single line of input

//define function headers to call in main
bool ValueOfZero(char arr[], size_t arrLen);
int Compare(const void* a, const void* b);

int main(int argc, char* argv[])
{
	char inputBuffer[MAX_LINE]; //stack allocated array used to temporary store users input before storing the input into the heap array userVals
	size_t arraySize = 10;  //variable used to contain the total number of elements in the heap array userVals
	double* userVals = malloc(arraySize * sizeof(double)); //heap array, used to store the user inputs, allocated dynamically
	double* arithPoint = userVals; //pointer to perform arithmetic on, so as to not disturb the free() function called at program's end
	size_t indexCount = 0; //keeps track of used elements in heap array

	//ensure that userVals was properly given memory
	if (userVals == NULL) {
		printf("Error insufficent memory\n");
		return EXIT_FAILURE;
	}

	//if the user provided a a file name, open the file and read from it
	if (argc > 1) {
		FILE* userFile = fopen(argv[1], "r"); //open the file passed as an argument as read-only

		//if the file name is invalid
		if (userFile == NULL) {
			printf("Error file provided couldn't be opened");
			return EXIT_FAILURE;
		}

		//read input to the buffer from the file untill EOF
		while (fgets(inputBuffer, MAX_LINE, userFile) != NULL) {

			inputBuffer[strlen(inputBuffer)] = '\0'; //append a null terminator to the end of the string

			if (strtod(inputBuffer, NULL) == 0) { //if strtod returns a value of 0, either the user entered 0 as a number, or input buffer contains letters

				//checks if inputbuffer contains exactly "end"
				if (strcmp(inputBuffer, "end") == 0) {
					break;
				}
				//else, checks if the user actually intended to enter 0.
				else if (!ValueOfZero(inputBuffer, strlen(inputBuffer))) {
					continue; //if the value wasn't 0.000... skip that input
				}
				else {
					*arithPoint = strtod(inputBuffer, NULL); //otherwise if it was 0.000... store it in the heap array
				}
			}
			else {
				*arithPoint = strtod(inputBuffer, NULL); //store the non-0 return value in the heap array
			}

			arithPoint++; //move to the next element in the dynamic heap array
			indexCount++; //increase the index counter by 1
			//checks if the array is full
			if (indexCount == arraySize) {
				arraySize *= 2;
				double* temp = (double*)realloc(userVals, arraySize * sizeof(double)); //doubles the size of the array
				if (temp != NULL) { //if realloc was succesful, assign userVals to the to reallocated array
					userVals = temp;
					arithPoint = userVals + indexCount;
				}
				else {
					printf("Error insufficient memory\n");
					return EXIT_FAILURE;
				}

			}
		}

		fclose(userFile); //close the open file

	}
	//if the user passed no arguments, read input from the keyboard
	else {
		printf("Enter a series of floating point numbers seperated by a space, terminated with 'end' or EOF\n");
		for (;;) {
			(void)scanf("%s", inputBuffer); //read a string and store it in inputBuffer
			inputBuffer[strlen(inputBuffer)] = '\0'; //append a null terminator to the end of the string

			if (strtod(inputBuffer, NULL) == 0) { //if strtod returns a value of 0, either the user entered 0 as a number, or input buffer contains letters

				//checks if inputbuffer contains exactly "end"
				if (strcmp(inputBuffer, "end") == 0) {
					break;
				}
				//else, checks if the user actually intended to enter 0.
				else if (!ValueOfZero(inputBuffer, strlen(inputBuffer))) {
					continue; //if the value wasn't 0.000... skip that input
				}
				else {
					*arithPoint = strtod(inputBuffer, NULL); //otherwise if it was 0.000... store it in the heap array
				}
			}
			else {
				*arithPoint = strtod(inputBuffer, NULL); //store the non-0 return value in the heap array
			}

			arithPoint++; //move to the next element in the dynamic heap array
			indexCount++; //increase the index counter by 1
			//checks if array is full
			if (indexCount == arraySize) {
				arraySize *= 2;
				double* temp = (double*)realloc(userVals, arraySize * sizeof(double)); //doubles the size of the array
				if (temp != NULL) { //if realloc was succesful, assign userVals to the to reallocated array
					userVals = temp;
					arithPoint = userVals + indexCount;
				}
				else {
					printf("Error insufficient memory\n");
					return EXIT_FAILURE;
				}

			}
		}
	}
	
	arithPoint -= indexCount; //return the arithmetic pointer to element 0 
	qsort(arithPoint, indexCount, sizeof(double), Compare); //sort the heap array

	//displays the basic statistics
	DrawLine(); 
	printf("%-25s %25zu\n", "# elements", indexCount);
	printf("%-25s %25.3f\n", "minimum", arithPoint[0]);
	printf("%-25s %25.3f\n", "maximum", arithPoint[indexCount - 1]);
	printf("%-25s %25.3f\n", "range", arithPoint[indexCount - 1] - arithPoint[0]);
	printf("%-25s %25.3f\n", "mean", CalcMean(arithPoint, indexCount));
	printf("%-25s %25.3f\n", "median", CalcMedian(arithPoint, indexCount));
	printf("%-25s %25.3f\n", "variance", CalcVariance(arithPoint, indexCount));
	printf("%-25s %25.3f\n", "std. dev.", sqrt(CalcVariance(arithPoint, indexCount)));
	DrawLine();
	printf("Frequency Table\n");

	int bucketCount[NUMBER_OF_BUCKETS] = { 0 }; //stack array to store the count of each bucket
	CreateFrequencyTable(arithPoint, indexCount, bucketCount); //generates and displays the frequency table

	DrawLine();
	printf("Histogram\n");
	DrawHistogram(bucketCount, sizeof(bucketCount) / sizeof(int), indexCount); //draws the historgram using bucket data generated by CreateFrequencyTable
	DrawLine();

	//converts all of the users values to their natural logarithms
	for (size_t i = 0; i < indexCount; i++) {
		*arithPoint = log(*arithPoint);
		arithPoint++;
	}
	arithPoint -= indexCount;

	printf("Frequency Table\n");
	int logBucket[NUMBER_OF_BUCKETS] = { 0 };
	CreateFrequencyTable(arithPoint, indexCount, logBucket); //generates and siaplys the frequency table
	DrawLine();
	printf("Log Histogram\n");
	DrawHistogram(logBucket, sizeof(logBucket) / sizeof(int), indexCount); //draws the histogram using bucket data generated by CreateFrequencyTable

	free(userVals); //deallocates the memory on the heap user for userVals to prevent memory leaks
	return EXIT_SUCCESS;
}


/* Function: ValueOfZero
*  Purpose: used for input validation in main, checks if the user intended to enter a 0, that is that the user only entered '0's and a single '.'
*  Returns: true if the user entered 0.0000..., and false if the user entered anything else
*/

bool ValueOfZero(char arr[], size_t arrLen) {
	bool zero = true;
	bool firstDecimal = true;

	for (size_t i = 0; i < arrLen; i++) {
		if (arr[i] != '0' && arr[i] != '.') {
			zero = false;
		}

		if (arr[i] == '.' && firstDecimal) {
			firstDecimal = false;
		}
		else if (!firstDecimal) {
			return false;
		}
	}

	return zero;
}

/* Function: compare
*  Purpose: compares the values of 2 dereferenced pointers cast to double pointers, used in qsort()
*  Returns: returns an integer value of the difference between the pointers
*  This function was retrieved from https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
*/

int Compare(const void* a, const void* b) {
	return (*(double*)a - *(double*)b);
}