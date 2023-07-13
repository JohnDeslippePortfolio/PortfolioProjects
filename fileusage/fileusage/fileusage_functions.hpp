#pragma once
/*
Name: John Deslippe
Filename: fileusage_functions.hpp
Due Date: 14 August, 2022
Date: 10 August, 2022
Version: 1.0
Purpose: header file to hold function declarations
*/



#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <regex>
#include <map>
#include <algorithm>

using namespace std;

//struct to store any user input in
struct argFlags {
	filesystem::path inputFolder = filesystem::current_path();
	string userFilter = ".*";
	bool reverse = false;
	bool sort = false;
	bool filter = false;
};

//Struct to store an individual file type's statistics in
struct fileStats {
	string fileExt;
	int fileCount = 0;
	uintmax_t fileSize = 0;
};

/*
Function: parseArgs
brief: Reads the users input and stores it accordingly
param: argc - # of items entered, argv - cstring provided by user, userFlags - struct to store the input into
return: void
*/
void parseArgs(int argc, char* argv[], argFlags& userFlags);

/*
Function: parseFileUsage
brief: processes the parsed users input accordingly, calling other functions declared here as needed to display the final output
param: userFlags - struct containg the parsed input
return: void
*/
void parseFileUsage(const argFlags& userFlags);

/*
Function: sortByExtension
brief: sorts a vector of filestats, using the fileExt value as the comparator
param: v - vector to be sorted
return: void
*/
void sortByExtension(vector<fileStats>& v);

/*
Function: sortBySize
brief: sorts a vector of filestats, using the fileSize value as the comparator
param: v - vector to be sorted
return: void
*/
void sortBySize(vector<fileStats>& v);

/*
Function: displayFileUsage
brief: displays the values contained in the vector to cout in descending order
param: fileData - vector to display to cout
return: void
*/
void displayFileUsage(const vector<fileStats>& fileData);

/*
Function: displayFileUsageReverse
brief: displays the values contained in the vector to cout in ascending order
param: fileData - vector to display to cout
return: void
*/
void displayFileUsageReverse(const vector<fileStats>& fileData);

/*
Function: commaSeperate
brief: display a numerical value with comma seperators (1000 = 1,000)
param: i - number to add commas to
return: the processed number as a astring
*/
string commaSeperate(uintmax_t i);

/*
Function: displayHelp
brief: displays usage information on the program
param: none
return: void
*/
void displayHelp();