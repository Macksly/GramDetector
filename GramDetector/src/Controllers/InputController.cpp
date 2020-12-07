#include "InputController.h"
#include <iostream>
#include <string>

std::string GramDetector::Controllers::InputController::getSentence()
{ 
	std::cout << "please enter a sentence:" << std::endl;

	std::cin.ignore();
	std::string retVal;
	std::getline(std::cin, retVal);

	return retVal;
}

int GramDetector::Controllers::InputController::getGramType()
{
	system("CLS");

	std::cout << "Please enter the number of which gramtype you want to test and press <ENTER>" << std::endl;
	std::cout << "0 - Pangram" << std::endl;
	std::cout << "1 - Autogram" << std::endl;

	int retval;
	std::cin >> retval;

	return retval;
}

int GramDetector::Controllers::InputController::getLangType()
{
	system("CLS");

	std::cout << "Please enter the number of which language you want to use and press <ENTER>" << std::endl;
	std::cout << "0 - Nederlands" << std::endl;
	std::cout << "1 - English" << std::endl;

	int retval;
	std::cin >> retval;

	return retval;
}
