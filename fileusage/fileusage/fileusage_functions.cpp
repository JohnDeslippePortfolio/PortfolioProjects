/*
Name: John Deslippe
Filename: fileusage_functions.cpp
Due Date: 14 August, 2022
Date: 10 August, 2022
Version: 1.0
Purpose: Contains the functions outlined in corresponding header file
*/

#include "fileusage_functions.hpp"

void parseArgs(int argc, char* argv[], argFlags& userFlags) {
	//grab the users input
	vector<string> userArgs(&argv[1], &argv[argc]); //vector to store user args in
	//interpret the input, toggle any appropriate flags
	while (!userArgs.empty()) {
		if (userArgs.front().at(0) == '-') { //if the arg starts with - it must be an argument
			if (userArgs.front() == "--help" || userArgs.front() == "-h") {
				displayHelp();
				exit(EXIT_SUCCESS);
			}
			else {
				for (string::iterator sit = userArgs.front().begin() + 1; sit != userArgs.front().end(); ++sit) {
					if (*sit == 'r') {
						userFlags.reverse = true;
					}
					else if (*sit == 's') {
						userFlags.sort = true;
					}
					else if (*sit == 'x') {
						userFlags.filter = true;
						//The next string will be the REGEX Expression, need to extract that and remove it from vector
						userFlags.userFilter = userArgs.at(1);
						userArgs.erase(userArgs.begin()+1);
					}
				}
			}
		}
		else {
			userFlags.inputFolder = userArgs.front();
		}
		userArgs.erase(userArgs.begin());
	}

}

void parseFileUsage(const argFlags& userFlags) {
	vector<fileStats> fileData; //A vector to store the data parsed on each file, done as a vector for simplified sorting
	fileStats tempData; //A temporary holding place to push into the vector

#ifndef NDEBUG //if the debug version is running display the users inputs at the top of the console
	{
		string passedSwitches = "";
		if (userFlags.reverse)
			passedSwitches.append("r");
		if (userFlags.sort)
			passedSwitches.append("s");

		cout << "DEBUG: command line " << passedSwitches << "x \"" << userFlags.userFilter <<"\" folder: " << userFlags.inputFolder << endl;

	}
#endif
	filesystem::recursive_directory_iterator di(userFlags.inputFolder); //iterator to traverse the path provided
	for (filesystem::path filePath : di) {

		string fileType = ""; //variable to hold the extension
		uintmax_t currentFileSize = 0; //variable to hold the filsize
		regex definedFilter(userFlags.userFilter); //regex to compare against if user has provided one
		//extract file extension from the path
		
		fileType = filePath.extension().string();
		currentFileSize = filesystem::file_size(filePath);
		bool extExists = false; //boolean used to determine if the file already has an element in the vector
		vector<fileStats>::size_type i = 0; //variable used to traverse elements in for loop

		if (!userFlags.filter) {
			if (filesystem::is_regular_file(filePath)) {
				for (; i < fileData.size(); ++i) {
					if (fileData[i].fileExt == fileType) { //iterate through the vector, looking if there is a match for the extension
						extExists = true;
						break;
					}
				}

				if (extExists) {//if there is already an elemnt store the data there
					fileData[i].fileCount += 1;
					fileData[i].fileSize += currentFileSize;
				}
				else {//otherwise create a new element
					tempData.fileExt = fileType;
					tempData.fileCount = 1;
					tempData.fileSize = currentFileSize;
					fileData.push_back(tempData);
				}
			}
		}
		else {
			if (filesystem::is_regular_file(filePath)) {
				if (regex_match(fileType, definedFilter)) {
					for (; i < fileData.size(); ++i) {
						if (fileData[i].fileExt == fileType) {
							extExists = true;
							break;
						}
					}

					if (extExists) {
						fileData[i].fileCount += 1;
						fileData[i].fileSize += currentFileSize;
					}
					else {
						tempData.fileExt = fileType;
						tempData.fileCount = 1;
						tempData.fileSize = currentFileSize;
						fileData.push_back(tempData);
					}
				}
			}
		}
	}
	cout << setw(16) << "Ext" << setw(8) << "#" << setw(15) << "Total\n" << endl;
	if (userFlags.sort)
		sortBySize(fileData);
	else
		sortByExtension(fileData);

	if (userFlags.reverse)
		displayFileUsageReverse(fileData);
	else
		displayFileUsage(fileData);


}

void displayHelp() {
	cout << "fileusage {v3.0.0} (c) 2016-20, Garth Santor" << endl;
	cout << "\n\tUsage: fileusage [--help] [-hrs(x regularexpression)] [folder]" << endl;
	cout << "\tswitches:" << endl;
	cout << "\t\th\thelp" << endl;
	cout << "\t\tr\treverse the order of the listing" << endl;
	cout << "\t\ts\tsort by file sizes" << endl;
	cout << "\t\tx\tfilter with a regular expression" << endl;
	cout << "\n\tfolder" << endl;
	cout << "\t\tstarting folder or current folder if not provided" << endl;
}

void sortByExtension(vector<fileStats>& v) {
	sort(v.begin(), v.end(), [](fileStats a, fileStats b) {
		return a.fileExt < b.fileExt;
		});
}

void sortBySize(vector<fileStats>& v) {
	sort(v.begin(), v.end(), [](fileStats a, fileStats b) {
		return a.fileSize < b.fileSize;
		});
}

void displayFileUsage(const vector<fileStats>& fileData) {
	uintmax_t totalFileSize = 0;
	int totalFileCount = 0;
	for (vector<fileStats>::size_type i = 0; i < fileData.size(); ++i) {
		cout << setw(16) << fileData[i].fileExt << setw(8) << fileData[i].fileCount << setw(15) << commaSeperate(fileData[i].fileSize) << endl;
		totalFileCount += fileData[i].fileCount;
		totalFileSize += fileData[i].fileSize;
	}
	cout << endl;
	cout << setw(16) << fileData.size() << setw(8) << totalFileCount << setw(15) << commaSeperate(totalFileSize) << endl;
}

void displayFileUsageReverse(const vector<fileStats>& fileData) {
	uintmax_t totalFileSize = 0;
	int totalFileCount = 0;
	
	for (vector<fileStats>::size_type i = fileData.size() - 1; i > 0; i--) {
		cout << setw(16) << fileData[i].fileExt << setw(8) << fileData[i].fileCount << setw(15) << commaSeperate(fileData[i].fileSize) << endl;
		totalFileCount += fileData[i].fileCount;
		totalFileSize += fileData[i].fileSize;
	}

	cout << setw(16) << fileData[0].fileExt << setw(8) << fileData[0].fileCount << setw(15) << commaSeperate(fileData[0].fileSize) << endl;
	totalFileCount += fileData[0].fileCount;
	totalFileSize += fileData[0].fileSize;

	cout << endl;
	cout << setw(16) << fileData.size() << setw(8) << totalFileCount << setw(15) << commaSeperate(totalFileSize) << endl;
}

string commaSeperate(uintmax_t i) {
	string o = to_string(i);

	int count = 0;
	for (size_t i = o.size() - 1; i > 0; --i) {
		count++;
		if (count == 3) {
			o.insert(i, ",");
			count = 0;
		}

	}

	return o;
}