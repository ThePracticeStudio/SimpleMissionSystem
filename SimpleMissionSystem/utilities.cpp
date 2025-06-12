#include <iostream>

#include "../includes/utilities.h"

bool getValidInput(const std::string& prompt, int& n) {
	std::cout << prompt;
	std::cin >> n;
	std::cout << '\n';

	return !std::cin.fail();
}
void ClearAndIgnore() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void printErrorMessage(const std::exception& e) {
	std::cout << e.what();
}