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
const char* AbortCopyCommand::what() {
	colorMe(COLOR_FUCHSIA);
	return "Aborted\n";
}
const char* MissingOperands::what() {
	colorMe(COLOR_FUCHSIA);
	return "Command is missing operands. Please consult Help\n";
}
const char* OperationNotSupported::what() {
	colorMe(COLOR_FUCHSIA);
	return "Operation for the composite command is not supported. Please consult Help\n";
}
const char* NotExistingCriterium::what() {
	colorMe(COLOR_FUCHSIA);
	return "Criterium you have chosen is not existing. Please consult Help\n";
}