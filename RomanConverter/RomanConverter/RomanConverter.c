/* File Name: RomanConverter
* Author: John Deslippe 0754326
* Date: June 1st, 2022
* Platform toolset: Visual Studio 2022 V143
* Visual Studio Version: 17.1.6
* Compiler Version: Microsoft (R) C/C++ Optimizing COmpiler Version 19.31.31107 
* Purpose: Reads the users input, determines if the value entered is a roman numeral or an arabic number
*		   Converts the entered value to the other type and displays it, Program continues until user specifies with input of "quit"
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define MAX_ARR 256 //Defines max array size for user input
#define MAX_IN(X) #X //"stringerizes" the value of x
#define IN(X) MAX_IN(X) //allows for inline displaying of the value contained in max in for use in a scanf parameter


/* Function: ReadRoman
*  Purpose: read user input chars from an array and assign the raw individual roman numerals value to corresponding elements in an array of type double
*  Parameters: accepts users input as a char array, and a double array to store the arabic values of the roman numerals in
*  Returns: void
*/
void ReadRoman(char input[], double value[]) {
	size_t vin = 0; 
	for (size_t i = 0; i < strlen(input); i++) { //iterate through the entire user input array
		//if statement checks each value at the current element to determine what roman numeral it is, and stores the arabic value in the corresponding element in the double array
		if (input[i] == 'S') { 
			value[i] = (1.0 / 2.0);
		}
		else if (input[i] == '.') {
			value[i] = (1.0 / 12.0);
		}
		else if (input[i] == 'I') {
			value[i] = 1.0;
		}
		else if (input[i] == 'V') {
			value[i] = 5.0;
		}
		else if (input[i] == 'X') {
			value[i] = 10.0;
		}
		else if (input[i] == 'L') {
			value[i] = 50.0;
		}
		else if (input[i] == 'C') {
			value[i] = 100.0;
		}
		else if (input[i] == 'D') {
			value[i] = 500.0;
		}
		else if (input[i] == 'M') {
			value[i] = 1000.0;
		}
		else if (input[i] == '_' || input[i] == '-') { //if the user has entered a viniculum
			if (vin == 0) { //if this is the first viniculum
				for (size_t j = 0; j < i; j++) { //starting at element 0 in the array, multiply all values before the viniculum by 1000
					value[j] *= 1000;
				}
				vin = i; //stores the location of the current viniculum
			}
			else { //if this isn't the first viniculum
				for (size_t j = vin + 1; j < i; j++) { //starting at the element immediately after the previous viniculum, multiply all values before the new viniculum by 1000
					value[j] *= 1000;
				}
				vin = i; //stores the location of the current viniculum
			}
		}
	}
}

/* Function: ConvertToDouble
*  PUrpose: Reads the values in an array containing the raw values of the roman numerals entered and calculates the net value of the user entered numerals
*  Parameters: a double array containing the arabic values of a roman numeral entered by the user, the size of the array
*  Returns: double value as the sum total of the roman numeral value
*/
double ConvertToDouble(double value[], size_t length) {
	double convert = 0; //double variable to hold the value of the users input
	size_t i = 0; //

	while (i < length){
		if (i == length - 1) { //only runs when this is the last value
			convert += value[i]; //adds the final value
			i++;
		}
		else if (value[i] < value[i + 1] && value[i]!= 0) { //if the value to the right of the current value is greater than the current value, ignores zeroes in the array, caused by viniculum inputs
			convert += value[i + 1] - value[i]; //add the value to the right and subtract the current value (i.e. if the value is I(1) V(5) add 5 and subtract 1 to get a net 4
			i += 2; //increment by 2 to skip the next value as it has already been incorporated into the converted value

		}
		else { //otherwise, simply add the current value to the conversion
			convert += value[i];
			i++;
		}
	}

	return convert;
}

/* Function: ConvertToRoman
*  Purpose: Reads a user entered double and returns the corresponding roman numeral characters
*  Parameters: a char array to store the roman numerals output by the function, and a double array containing the arabic number supplied by the user
*  Returns: void
*/
void ConvertToRoman(char romanOut[], double arabicIn) {
	while (arabicIn != 0.0) { //Continue until the users input has been completely converted
		if (arabicIn >= 4000) { //if the value is greater than 3999, the maximum value of a standard roman numeral, it must contain a viniculum
			double excessRoman = (arabicIn - fmod(arabicIn, 1000)) / 1000; //stores the value greater than 3999 and simplifies it down into the 1's column
			arabicIn -= excessRoman * 1000; //subtracts the excess value from the users input

			while (excessRoman > 0) { //until the excess has been reduced to 0

				double vin = 0;//a value to store the viniculum portion in
				if (excessRoman >= 4000) {  //if excessRoman, which has been simplified into it's own seperate base roman numeral has an excess portion in it 
					vin = (excessRoman - fmod(excessRoman, 1000)) / 1000; //store that excess in vin
					excessRoman -= vin * 1000;//remove that portion from excess
				}
				else { //if excess roman is 3999 or lower
					vin = excessRoman; //assign the value to vin
					excessRoman -= vin; //remove the value from excessRoman
				}
				
				while (vin > 0) { //repeat until all of the viniculum value has been dealt with

					//if statement checks if the value is greater than a roman numeral, 
					//and then concatenates that corresponding roman numeral onto the romanOut array and subtracts the value of that numeral
					if (vin >= 1000) {
						strcat(romanOut, "M");
						vin -= 1000;
					}
					else if (vin >= 900) {
						strcat(romanOut, "CM");
						vin -= 900;
					}
					else if (vin >= 500) {
						strcat(romanOut, "D");
						vin -= 500;
					}
					else if (vin >= 400) {
						strcat(romanOut, "CD");
						vin -= 400;
					}
					else if (vin >= 100) {
						strcat(romanOut, "C");
						vin -= 100;
					}
					else if (vin >= 90) {
						strcat(romanOut, "XC");
						vin -= 90;
					}
					else if (vin >= 50) {
						strcat(romanOut, "L");
						vin -= 50;
					}
					else if (vin >= 40) {
						strcat(romanOut, "XL");
						vin -= 40;
					}
					else if (vin >= 10) {
						strcat(romanOut, "X");
						vin -= 10;
					}
					else if (vin >= 9) {
						strcat(romanOut, "IX");
						vin -= 9;
					}
					else if (vin >= 5) {
						strcat(romanOut, "V");
						vin -= 5;
					}
					else if (vin >= 4) {
						strcat(romanOut, "IV");
						vin -= 4;
					}
					else if (vin >= 1) {
						strcat(romanOut, "I");
						vin -= 1;
					}
				}
				strcat(romanOut, "-"); //once the entire portion of the value greater than 3999 is dealt with, concatenate a '-' onto the end
			}
			
		}
		else {
			//if statement checks if the value is greater than a roman numeral, 
			//and then concatenates that corresponding roman numeral onto the romanOut array and subtracts the value of that numeral
			if (arabicIn >= 1000) {
				strcat(romanOut, "M");
				arabicIn -= 1000;
			}
			else if (arabicIn >= 900) {
				strcat(romanOut, "CM");
				arabicIn -= 900;
			}
			else if (arabicIn >= 500) {
				strcat(romanOut, "D");
				arabicIn -= 500;
			}
			else if (arabicIn >= 400) {
				strcat(romanOut, "CD");
				arabicIn -= 400;
			}
			else if (arabicIn >= 100) {
				strcat(romanOut, "C");
				arabicIn -= 100;
			}
			else if (arabicIn >= 90) {
				strcat(romanOut, "XC");
				arabicIn -= 90;
			}
			else if (arabicIn >= 50) {
				strcat(romanOut, "L");
				arabicIn -= 50;
			}
			else if (arabicIn >= 40) {
				strcat(romanOut, "XL");
				arabicIn -= 40;
			}
			else if (arabicIn >= 10) {
				strcat(romanOut, "X");
				arabicIn -= 10;
			}
			else if (arabicIn >= 9) {
				strcat(romanOut, "IX");
				arabicIn -= 9;
			}
			else if (arabicIn >= 5) {
				strcat(romanOut, "V");
				arabicIn -= 5;
			}
			else if (arabicIn >= 4) {
				strcat(romanOut, "IV");
				arabicIn -= 4;
			}
			else if (arabicIn >= 1) {
				strcat(romanOut, "I");
				arabicIn -= 1;
			}
			else if (arabicIn >= (1.0 / 2.0)) {
				strcat(romanOut, "S");
				arabicIn -= (1.0 / 2.0);
			}
			else if (arabicIn >= (1.0 / 12.0)) {
				strcat(romanOut, ".");
				arabicIn -= (1.0 / 12.0);
			}
			else {
				arabicIn = 0.0; //removes any remaining value that is too small for (1.0 / 12.0) to detect
			}
		}
	}
}

/* Function: ApostrophusConvert
*  Purpose: Reads user entered apostrophus characters and determins their arabic value
*  Parameters: Character array containing users input, and array index of the first ')' found i the input array
*  Returns: Integer value of the apostrophus
*/

int ApostrophusConvert(char input[], size_t i) {
	size_t lastOccur = i; //stores the last occurence of a ')' in the the user input array
	int c_count = 0; //stores the number of 'C' entered
	int aposCount = 0; //stores the number of ')' entered
	int total = 1000; //stores the total value of the apostrophus
	for (size_t j = i; input[j] == input[j + 1]; j++) { //beggining at the first ')' found, keeps checking the character to the right of it to see if it is also ')'
		lastOccur++; //Everytime the loop finds a ')' increment the value of lastOccur by 1
	}

	for (size_t j = 0; j <= lastOccur; j++) { //go through the array until the last occurnce of ')' found
		switch (input[j]) { //switch statement checking for 'C' or ')' and count the number of occurences
		case ('C'):
			c_count++;
			break;
		case (')'):
			aposCount++;
			break;
		}

		
	}
	
	strcpy(input, input + (lastOccur + 1)); //removes apostrophus portion of roman numeral entered to allow for reading of remaining characters

	if (c_count > aposCount) { //if there are more 'C' than ') ht eapostrophus is unbalanced and returns a value of 0
		printf("Error, apostrophus is unbalanced");
		return 0;
	}
	else if (c_count == aposCount) { //if they're even then the apostrophus will be base 1000 multiplied by the the number of 'C' & ')' 
		for (int i = 1; i < c_count; i++) {
			total *= 10;
		}
	}
	else if (c_count == 0) { //if there is no 'C' then the apostrophus will be base 500, multiplied by 10 for the number of ')'
		total = 500;
		for (int i = 1; i < aposCount; i++) {
			total *= 10;
		}
	}
	else { //otherwise, the apostrophus must be a combination
		int subtotal = 500; //declare a subtotal initialized to 500 for the unbalanced portion
		for (int i = 1; i < c_count; i++) { //mutiply the balanced portion by 10 for every 'C'
			total *= 10;
		}
		for (int i = 1; i < (aposCount - c_count); i++) { //multiple the unbalanced portion by 10 for every unbalanced ')' present in input
			subtotal *= 10;
		}
		total += subtotal; 
	}

	return total;
}



	int main() {
		printf("Roman/Arabic Converter\nType Quit to exit.\n"); 

		
		
		for (;;) {
			char input[MAX_ARR]; //Character array to store users input
			double arabicVal[MAX_ARR] = { 0 }; //double array to store the numerical values of the roman numerals entered in the input array
			bool isRoman = true; //boolean which defaults to true and remains true if the values in the input array aren't arabic numbers, and becomes false if they are arabic numbers
			double conversion = 0.0; //double variable to store the converted value of the roman numerals
			char romanOutput[256] = {0}; //array to store roman numeral characters for output, initialized to 0 aka ASCII value for NULL
			printf("Enter a value (Roman or Arabic): ");
			(void) scanf("%" IN(MAX_ARR) "s", input); //read users input, limited to the maximum possible elements in the input array
			input[strlen(input)] = '\0'; //zero terminating string

			for (size_t i = 0; i < strlen(input); i++) { //Converts all letters in array to upper case
				input[i] = toupper(input[i]);
			}
			
			if (strcmp(input, "QUIT") == 0) { //if user enters 'QUIT', immediately end 
				break;
			}
			
			for (size_t i = 0; i < strlen(input); i++) { //iterate through each element in the array
				if (input[i] >= 48 && input[i] <= 57) { //checking if the input is between ASCII values for 0-9, 
					isRoman = false; 
				}
				else if (input[i] == ')') {//Checking if apostrophus system has been entered
					if (i != 0 && input[i - 1] == 'I' && (i == 1 || input[i -2] == 'C')) { //determines that there is a I infront of the the ), and if the I isn't the first element, if there is a C in front of it
						conversion += ApostrophusConvert(input, i); //adds the value of the apostrophus to the conversion variable
					}
					
				}
			}

			if (isRoman) {
				ReadRoman(input, arabicVal); //reads the arabic values of the user entered roman numerals to the arabicVal array
				conversion += ConvertToDouble(arabicVal, strlen(input));//converts the raw values of the roman numerals to their true value
			}
			else {
				ConvertToRoman(romanOutput, strtod(input, NULL)); //reads the user input converted to type double, and stores the roman numeral out put to the romanOutput Array
			}
			

			if (isRoman) {
				int count = 0; //integer variable used to store required decimal precision
				float fraction = (float)fmod(conversion, 1.0); //variable used to store the fractional component of the user entered value
				while (fmod(fraction, 1.0) != 0) { //continue the body of this loop for as long as there is remainder of division by 1
					count++; //add one the required precision to outpu
					fraction *= 10; //multiply the fractional portion by 10 to shift all numbers left 1 column
				}
				printf("As an arabic number: %.*f\n", count, conversion); //display the value in conversion, with a decimal precision storeed in count
			}
			else {
					printf("As a roman numeral: %s\n", romanOutput); //displays the roman numeral converted from the users entered arabic value
			}
		}
}