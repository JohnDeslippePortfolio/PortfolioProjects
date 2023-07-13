#pragma once
/*
* File Name: CSVParser.hpp
* Author: John Deslippe
* Date: November 27th, 2022
* Purpose: Declares functions used for reading & writing to a csv file
*/
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "BreastCancer.hpp"

std::vector<BreastCancer> parseFileToVector(const std::string& filePath);

void ParseVectorToFile(std::vector<BreastCancer>& toParse);