#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>

#include "Mission.h"

bool getValidInput(const std::string& prompt, int& n);
void ClearAndIgnore();
void printErrorMessage(const std::exception& e);

#endif // UTILITIES_H