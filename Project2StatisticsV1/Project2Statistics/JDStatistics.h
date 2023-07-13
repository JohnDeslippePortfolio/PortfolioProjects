/* File Name: JDStatistics.h
* Author: John Deslippe 0754326
* Date: June 1st, 2022
* Platform toolset: Visual Studio 2022 V143
* Visual Studio Version: 17.1.6
* Compiler Version: Microsoft (R) C/C++ Optimizing COmpiler Version 19.31.31107
* Purpose: Contains the publicly avaliable functions used to calculate basic statistics
*/

#pragma once
#define NUMBER_OF_BUCKETS 10

double CalcMean(double userVals[], size_t length);

double CalcMedian(double userVals[], size_t length);

double CalcVariance(double userVals[], size_t length);

void CreateFrequencyTable(double userVals[], size_t length, int bucketCount[]);