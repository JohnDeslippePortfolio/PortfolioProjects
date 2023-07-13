/*
* File Name: CSVParser.cpp
* Author: John Deslippe
* Date: November 27th, 2022
* Purpose: Defines functions used for reading & writing to a csv file
*/

#include "CSVParser.hpp"
#include <iomanip>
using namespace std;
std::vector<BreastCancer> parseFileToVector(const std::string& filePath) {
	ifstream fileIn(filePath, ifstream::in);
	if (!fileIn) {
		cout << "Error opening file" << endl;
		exit(EXIT_FAILURE);
	}
	string readValues = "";
	
	vector<BreastCancer> allCSV;
	int badData = 0;
	int allData = 0;
	while (!fileIn.eof()) {
		allData++;
		BreastCancer csvBuf;
		bool validData = true;
		getline(fileIn, readValues);
		istringstream lineBuf(readValues);
		while (!lineBuf.eof()) {
			try {
				getline(lineBuf, readValues, ',');
				csvBuf.id = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.clumpThickness = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.uniformCellSize = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.uniformCellShape = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.marginalAdhesion = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.epithelialSize = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.bareNuclei = stoi(readValues);

				getline(lineBuf, readValues, ',');
				csvBuf.blandChromatin = stoi(readValues);
				

				getline(lineBuf, readValues, ',');
				csvBuf.normalNucleoli = stoi(readValues);
				

				getline(lineBuf, readValues, ',');
				csvBuf.mitoses = stoi(readValues);
				

				getline(lineBuf, readValues, ',');
				csvBuf.cancerClass = stoi(readValues);
			}
			catch (exception e) {
				validData = false;
				badData++;
			}
		}
		if (validData) {
			allCSV.push_back(csvBuf);
		}
	}
	
	fileIn.close();
	cout << "Total lines read " << allData << endl;
	cout << "Read " << allCSV.size() << " valid data sets" << endl;
	cout << "Ignored " << badData << " data sets due to bad values " << endl;
	return allCSV;
}

void ParseVectorToFile(std::vector<BreastCancer>& toParse) {
	ofstream fileOut(".\\results.csv", ofstream::out);
	if (!fileOut) {
		cout << "Error writing results to file" << endl;
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < toParse.size(); ++i)
		toParse[i].print(fileOut);


	fileOut.close();
}