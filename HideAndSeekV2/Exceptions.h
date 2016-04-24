#pragma once

#include <iostream>
#include <iomanip>

#include "ColorMe.h"

using namespace std;

class NonExistingOption : public exception {
public:
	const char* what();
};
class NonExistingCommand : public exception {
public:
	const char* what(); 
};
class CopyDirectoryToFileError : public exception {
public:
	const char* what();
};
class AbortCopyCommand : public exception {
public:
	const char* what();
};
class MissingOperands : public exception {
public:
	const char* what();
};



