// Message encoder/decoder using arrays
//			by: Mark Lasker

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


// Loop through 2D array to encode passed unencrypted string using "codex" which is a generated 2d key array

std::string encodeString(std::string decodedString, char codex[][5]) {

	std::string encodedMessage = "";

	for (char& c : decodedString) {

		if (isdigit(c)) {
			encodedMessage += c;
		}
		for (int h = 0; h < 5; h++) {
			for (int w = 0; w < 5; w++) {
				if (codex[h][w] == ::toupper(c)) {
					encodedMessage += codex[w][h];
				}
			}
		}
		if (c == ' ') {
			encodedMessage += ' ';
		}
	}

	std::transform(encodedMessage.begin(), encodedMessage.end(), encodedMessage.begin(), ::toupper);

	return encodedMessage;
}

// Loop through 2D array to decode passed encrypted string using "codex" which is a generated 2d key array
std::string decodeString(std::string encodedString, char codex[][5]) {

	std::string decodedMessage = "";

	for (char& c : encodedString) {

		if (isdigit(c)) {
			decodedMessage += c;
		}
		for (int h = 0; h < 5; h++) {
			for (int w = 0; w < 5; w++) {
				if (codex[h][w] == c) {
					decodedMessage += ::tolower(codex[w][h]);
				}
			}
		}
		if (c == ' ') {
			decodedMessage += ' ';
		}
	}

	//std::transform(decodedMessage.begin(), decodedMessage.end(), decodedMessage.begin(), ::tolower);

	return decodedMessage;
}

// Void process to create the "codex" which is the key to decode/encode strings with given keyword, read from file
void createCodex(std::string codeWord, char(myArr)[5][5]) {

	// Arrays used to create codex below
	char alphabet[25] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y' };
	char codeArr[50];

	// Read in code word and insert it into 2D array with code to skip duplicate letters
	int count = 0;
	for (char& c : codeWord) {
		bool exists = std::find(std::begin(codeArr), std::end(codeArr), c) != std::end(codeArr);
		if (!exists)
		{
			codeArr[count] = c;
			count++;
		}
	}

	// Fill the rest of the 2D array with the remaining letters of alphabet in order, again skipping duplicate letters
	for (int i = 0; i < 25; i++) {
		bool exists = std::find(std::begin(codeArr), std::end(codeArr), ::toupper(alphabet[i])) != std::end(codeArr);
		if (!exists){

			codeArr[count] = alphabet[i];
			count++;
		}
	}

	// Populate 2D codex array using the generated array from above
	int newCount = 0;
	for (int h = 0; h < 5; h++) {

		for (int w = 0; w < 5; w++) {

			myArr[h][w] = ::toupper(codeArr[newCount]);
			newCount++;
		}
	}

}

// Routine to open file, call functions to create code arrays, and then output to console
void processFile(std::string inputFile) {

	std::ifstream infile;
	infile.open(inputFile);

	std::string s;
	getline(infile, s);


	char myArr[5][5];
	createCodex(s, myArr);

	std::transform(s.begin(), s.end(), s.begin(), ::toupper);

	std::cout << "Keyword is: " << s << std::endl << std::endl;
	std::cout << "  | 0 | 1 | 2 | 3 | 4 |" << std::endl;

	for (int h = 0; h < 5; h++) {

		std::cout << "----------------------\n " << h << "|";

		for (int w = 0; w < 5; w++) {

			std::cout << " " << myArr[h][w] << " |";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
	while (getline(infile, s)) {

		std::string str = s.substr(0, 1);
		std::string str2 = s.substr(2);

		std::cout << "******************************************************************************************************" << std::endl;
		std::cout << str2 << std::endl;

		if (str == "E") {

			std::cout << "Encrypts to\n";
			std::cout << encodeString(str2, myArr) << std::endl;
		}
		else if (str == "D") {
			std::cout << "Decrypts to\n";
			std::cout << decodeString(str2, myArr) << std::endl;
		}

	}
}

int main()
{
	processFile("input.txt");

	return 0;
}

