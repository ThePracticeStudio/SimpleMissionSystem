#include <iostream>

#include "../includes/utilities.h"

// Get a variable and let the user read it. Returns true if input is valid, false if not
bool getValidInput(const std::string& prompt, int& n) {
	std::cout << prompt;
	std::cin >> n;
	std::cout << '\n';

	return !std::cin.fail();
}

// Clears the input buffer
void ClearAndIgnore() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Prints the error message of an exception
void printErrorMessage(const std::exception& e) {
	std::cout << e.what() << "\n\n";
}