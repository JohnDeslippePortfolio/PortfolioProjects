/*
Name: John Deslippe
Filename: fileusage.cpp
Due Date: 14 August, 2022
Date: 10 August, 2022
Version: 1.0
Purpose: file containing the main function, calling the necessary functions from fileusage_functions
*/

#include "fileusage_functions.hpp"

int main(int argc, char* argv[]) {
	argFlags userFlags;

	parseArgs(argc, argv, userFlags);

	try { //parseFileUsage potentially throws a filesystem exception if the user passes an invalid path
		parseFileUsage(userFlags);
	}
	catch(exception e) {
		cout << e.what() << endl;
		return(EXIT_FAILURE);
	}
}