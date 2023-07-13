#pragma once
/*
* File Name: BreastCancer.hpp
* Author: John Deslippe
* Date: November 27th, 2022
* Purpose: Declares the BreastCancer class, which contains attributes to contain all patient data
*/
#include <string>
#include <iostream>
#include <fstream>
class BreastCancer {
public:
	unsigned id;
	unsigned clumpThickness;
	unsigned uniformCellSize;
	unsigned uniformCellShape;
	unsigned marginalAdhesion;
	unsigned epithelialSize;
	unsigned bareNuclei;
	unsigned blandChromatin;
	unsigned normalNucleoli;
	unsigned mitoses;
	unsigned cancerClass;


	/*
	* Name: print
	* Purpose: prints out all values contained in a BreastCancer object to a ostream received as a argument
	* Accepts:output - ostream object to print to
	* Returns: void
	*/
	void print(std::ofstream& output);
};

