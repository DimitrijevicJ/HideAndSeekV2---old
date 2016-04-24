#include "Exceptions.h"

const char* NonExistingOption::what(){
	colorMe(COLOR_FUCHSIA);
	return "The option you have chosen does not exist. Please consult Help\n";
}

const char* NonExistingCommand::what(){
	colorMe(COLOR_FUCHSIA);  
	return "The command you wish to execute does not exist. Please consult Help\n";
}

const char* CopyDirectoryToFileError::what() {
	colorMe(COLOR_FUCHSIA);
	return "You can't copy directory to a file. Please consult Help\n";
}