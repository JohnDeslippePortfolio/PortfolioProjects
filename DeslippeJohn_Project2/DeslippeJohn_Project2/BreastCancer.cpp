/*
* File Name: BreastCancer.cpp
* Author: John Deslippe
* Date: November 27th, 2022
* Purpose: Defines member functions of BreastCancer class
*/

#include "BreastCancer.hpp"

void BreastCancer::print(std::ofstream& output) {
	output << id << "," << clumpThickness << "," << uniformCellSize << "," << uniformCellShape << "," << marginalAdhesion << ","
		<< epithelialSize << "," << bareNuclei << "," << blandChromatin << "," << normalNucleoli << "," << mitoses << "," << cancerClass
		<<std::endl;
}

