#include "InputController.h"
#include <iostream>
#include <string>

std::string GramDetector::Controllers::InputController::getSentence()
{ 
	std::cout << "Please enter a sentence:" << std::endl;

	std::cin.ignore();
	std::string retVal;
	std::getline(std::cin, retVal);

	return retVal;
}

int GramDetector::Controllers::InputController::getGramType()
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
		std::cout << "> Invalid input, the default value autogram has been chosen" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	return retval;
}

int GramDetector::Controllers::InputController::getLangType()
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
		std::cout << "The default value language (Nederlands) has been chosen" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	return retval;
}
