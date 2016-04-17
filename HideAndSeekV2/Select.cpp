#include "Select.h"

//Reference : This awesome function has been donated by some brilliant internet user, and I will use this opportunity to thank him
//http://www.geeksforgeeks.org/wildcard-character-matching/
bool match(char *first, char * second)
{
	// If we reach at the end of both strings, we are done
	if (*first == '\0' && *second == '\0')
		return true;

	// Make sure that the characters after '*' are present
	// in second string. This function assumes that the first
	// string will not contain two consecutive '*'
	if (*first == '*' && *(first + 1) != '\0' && *second == '\0')
		return false;

	// If the first string contains '?', or current characters
	// of both strings match
	if (*first == '?' || *first == *second)
		return match(first + 1, second + 1);

	// If there is *, then there are two possibilities
	// a) We consider current character of second string
	// b) We ignore current character of second string.
	if (*first == '*')
		return match(first + 1, second) || match(first, second + 1);
	return false;
}

void Select::run(chars params, string param1, string param2) {
	Selection* select = new Selection(param1);
	for (auto& file : recursive_directory_iterator(current_path())) {
		string fileToAdd;
		if (params.size()>0 && params[0] == 'p') {
			fileToAdd = absolute(file.path()).string();
		}
		else if (params.size() == 0 || params[0] == 'f') {
			fileToAdd = file.path().filename().string();
		}
		else throw NonExistingOption();
		if (match(const_cast<char*>(param2.c_str()), const_cast<char*>(fileToAdd.c_str())))
			(*select) += new File(absolute(file.path()));
	}
	Selections::addSelection(select);
}
