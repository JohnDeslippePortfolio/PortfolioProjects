/* File Name: JDStatistics.c
* Author: John Deslippe 0754326
* Date: June 1st, 2022
* Platform toolset: Visual Studio 2022 V143
* Visual Studio Version: 17.1.6
* Compiler Version: Microsoft (R) C/C++ Optimizing COmpiler Version 19.31.31107
* Purpose: Contains functions used to calculate basic statistics
*/
#include <stdlib.h>

/* Function: CalcMean
*  Purpose: Calculates the mean of a dataset
*  Returns: the mean of the dataset as type double
*/

double CalcMean(double userVals[], size_t length) {
	double mean = 0.0;

	for (size_t i = 0; i < length; i++) {
		mean += userVals[i];
	}

	mean /= length;

	return mean;
}

/* Function: CalcMedian
*  Purpose: Calculates the median of a dataset
*  Returns: the median of the dataset as type double
*/

double CalcMedian(double userVals[], size_t length) {
	double median = 0.0;

	if (length % 2 == 0) { //if there is an even number of elements in the dataset
		median = (userVals[(length - 1) / 2] + userVals[(length + 1) / 2]) / 2;
	}
	else { //otherwise it must be an odd number of elements
		
		median = userVals[length / 2];
	}

	return median;
}

/* Function: CalcVariance
*  Purpose: Calculates the variance of a dataset
*  Returns: the variance of the dataset as type double
*/

double CalcVariance(double userVals[], size_t length) {
	double mean = CalcMean(userVals, length);
	double variance = 0;

	for (size_t i = 0; i < length; i++) {
		variance += (userVals[i] - mean) * (userVals[i] - mean);
	}

	variance /= length;

	return variance;
}

/* Function: CreateFrequencyTable
*  Purpose: generates a frequency table of ten buckets based off of a sorted list of values. Prints the resulting frequncy table to stdout 
*  Returns: void
*/

void CreateFrequencyTable(double userVals[], size_t length, int bucketCount[]) {
	double bucketSize = 0.1 * (userVals[length - 1] - userVals[0]); //contains 10% of the range, 
	double currentBucket = userVals[0]; //used to keep track of the lowest value of the current bucket

	
	size_t j = 0;
	int lastBucket = 0; //flag used to break out of loop

	for (size_t i = 0; i < length; i++) {
		if (userVals[i] >= currentBucket && userVals[i] < (currentBucket + bucketSize)) {
			bucketCount[j]++;
		}
		else //otherwise the value is outside of the range of the current bucket
		{
			while (userVals[i] >= (currentBucket + bucketSize)) {
				currentBucket += bucketSize; //go up to the next bucketsize
				j++;
				if (j == 9) { //if we have gone through every other bucket
					bucketCount[9] = length - i; //since the array is sorted, any remaining elements belong to the final bucket
					lastBucket = 1;
					break;
				}
			}
			if (lastBucket == 1) { //flag to break from external loop
				break;
			}
		
			bucketCount[j]++;
		}
	}

	currentBucket = userVals[0]; //reset the current bucket to the beginning
	//prints the labels and value of each bucket
	for (size_t i = 0; i < 9; i++) {
		printf(" %c [ %5.1f .. %5.1f) = %6d : %6.2f%%\n", 'A' + i, currentBucket, currentBucket + bucketSize, bucketCount[i], (bucketCount[i] / (double)length) * 100);
		currentBucket += bucketSize;
	}
	printf(" %c [ %5.1f .. %5.1f] = %6d : %6.2f%%\n", 'J', currentBucket, currentBucket + bucketSize, bucketCount[9], (bucketCount[9] / (double)length) * 100);
	

}