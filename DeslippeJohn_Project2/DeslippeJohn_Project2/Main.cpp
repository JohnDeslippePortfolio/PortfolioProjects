#include <iostream>
#include <string>
#include "BinaryTree.hpp"
#include "CSVParser.hpp"

using namespace std;
int main() {
	cout << "Enter path of file containing unformatted data\noutput will be saved in same location" << endl;
	string filePath; //= ".\\unformatted_data_v1.0.0.csv";
	getline(cin, filePath);
	cout << endl;
	BinaryTree prunedTree;
	prunedTree.buildPrunedTree();

	int maligCount = 0;
	int benignCount = 0;
	vector<BreastCancer> allData = parseFileToVector(filePath);
	for (size_t i = 0; i < allData.size(); ++i) {
		prunedTree.perform(allData[i], prunedTree.getRoot());
		if (allData[i].cancerClass == 2)
			benignCount++;
		else
			maligCount++;
	}
	
	cout << "\nMalignant Cases: " << maligCount << endl;
	cout << "Benign Cases: " << benignCount << "\n" << endl;

	ParseVectorToFile(allData);
	cout << "results stored in results.csv" << endl;
}