#include "IOController.h"
#include <iostream>
#include <string>

using namespace GramDetector;

std::string Controllers::IOController::getSentence() const
{ 
	std::cout << "Please enter a sentence:" << std::endl;

	std::cin.ignore();
	std::string retVal;
	std::getline(std::cin, retVal);

	std::transform(retVal.begin(), retVal.end(), retVal.begin(), [](unsigned char c) {return std::tolower(c); });

	return retVal;
}

const int Controllers::IOController::getGramType() const
{
	std::cout << "Please enter the number of which gramtype you want to test and press <ENTER>" << std::endl;
	std::cout << "0 - Autogram" << std::endl;
	std::cout << "1 - Pan-Autogram" << std::endl;

	int retval;

	try {
		std::cin >> retval;

		if (std::cin.fail()) {
			throw std::exception();
		}
	}
	catch (std::exception e) {
		std::cout << "Invalid input, the default value (Autogram) has been chosen" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	return retval;
}

const int Controllers::IOController::getLangType() const
{
	std::cout << "Please enter the number of which language you want to use and press <ENTER>" << std::endl;
	std::cout << "0 - Nederlands" << std::endl;
	std::cout << "1 - English" << std::endl;

	int retval;

	try {
		std::cin >> retval;

		if (std::cin.fail()) {
			throw std::exception();
		}
	}
	catch (std::exception e) {
		std::cout << "Invalid input, The default value language (Nederlands) has been chosen" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	return retval;
}

void Controllers::IOController::printSucces(const std::string& result, const int seconds, const std::string& input)
{
	system("CLS");

	std::cout << "*** Autogram Found! ***" << "\n";

	std::cout << "Duration: " << seconds << " seconds" << "\n";
	std::cout << "Input: " << input << "\n";
	std::cout << "Autogram: " << result << "\n";
	std::cout << "***********************" << "\n";

	std::getchar();
}