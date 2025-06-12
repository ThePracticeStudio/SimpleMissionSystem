#include <vector>
#include <iostream>

#include "../includes/Helpers.h"

const std::string projectName = "Simple Mission System";
const std::string hoursTaken = "Approximately 6 hours";
const std::string studioName = "ThePracticeStudio";
const std::string licenseName = "MIT License";

const std::vector<std::string> devNames = {
	"Kevin4e"
};

// Prints project information such as name, hours taken, studio name, and license.
void printProjectInfo() {
	std::cout << "Project name: " << projectName << '\n';
	std::cout << "Hours taken: " << hoursTaken << '\n';
	std::cout << "Made by: " << studioName << '\n';
	std::cout << "License: " << licenseName << '\n';

	std::cout << '\n';
}

// Prints the list of developer names (credits)
void printCredits() {
	std::cout << "Credits: \n";
	for (const auto& devName : devNames)
		std::cout << devName << '\n';

	std::cout << '\n';
}