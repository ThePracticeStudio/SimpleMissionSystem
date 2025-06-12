#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>

#include "Mission.h"

// Get a variable and let the user read it. Returns true if input is valid, false if not
bool getValidInput(const std::string& prompt, int& n);

// Clears the input buffer
void ClearAndIgnore();

// Prints the error message of an exception
void printErrorMessage(const std::exception& e);

#endif // UTILITIES_H