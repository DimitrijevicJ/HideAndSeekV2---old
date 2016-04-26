#include "Select.h"

Select* Select::select = new Select();

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


Selection* selectName(string name, chars params, string criterium) {
	Selection* select = new Selection(name);
	criterium.erase(0, 5);

	for (auto& file : recursive_directory_iterator(current_path())) {
		string fileToAdd;
		if (params.size() > 0 && params[0] == 'p') {
			fileToAdd = absolute(file.path()).string();
		}
		else if (params.size() == 0 || params[0] == 'f') {
			fileToAdd = file.path().filename().string();
		}
		else throw NonExistingOption();
		if (match(const_cast<char*>(criterium.c_str()), const_cast<char*>(fileToAdd.c_str())))
			(*select) += new File(absolute(file.path()));
	}
	return select;
}
Selection* selectSize(string name, chars params, string criterium) {
	Selection* select = new Selection(name);

	int isUpper = 0, isLower = 0, isEqual=0, limit;
	if (criterium[4] == '<') isUpper = 1;
	else if (criterium[4] == '=') isEqual = 1;
	else isLower = 1;
	criterium.erase(0, 5);
	limit = atoi(criterium.c_str());

	for (auto& file : recursive_directory_iterator(current_path())) {
		string fileToAdd;
		if (params.size() > 0 && params[0] == 'p') {
			fileToAdd = absolute(file.path()).string();
		}
		else if (params.size() == 0 || params[0] == 'f') {
			fileToAdd = file.path().filename().string();
		}
		else throw NonExistingOption();
		
		int size = PrintDirectoryContents::fetch()->fileSize(path(fileToAdd));
		if (isLower&&size>=limit)
			(*select) += new File(absolute(file.path()));
		else if (isUpper&&size <= limit)
			(*select) += new File(absolute(file.path()));
		else if (isEqual&&size == limit)
			(*select) += new File(absolute(file.path()));
	}
	return select;
}
Selection* selectTime(string name, chars params, string criterium) {
	Selection* select;

	int isUpper = 0, isLower = 0, isEqual = 0;
	if (criterium[4] == '<') isUpper = 1;
	else if (criterium[4] == '=') isEqual = 1;
	else isLower = 0;
	criterium.erase(0, 5);

	for (auto& file : recursive_directory_iterator(current_path())) {
		string fileToAdd;
		if (params.size() > 0 && params[0] == 'p') {
			fileToAdd = absolute(file.path()).string();
		}
		else if (params.size() == 0 || params[0] == 'f') {
			fileToAdd = file.path().filename().string();
		}
		else throw NonExistingOption();

		auto ftime = last_write_time(file);
		if (isLower&&difftime(decltype(ftime)::clock::to_time_t(ftime),SetTimeStamp::fetch()->getTime(criterium))<=0)
			(*select) += new File(absolute(file.path()));
		else if (isUpper&&difftime(decltype(ftime)::clock::to_time_t(ftime), SetTimeStamp::fetch()->getTime(criterium)) >= 0)
			(*select) += new File(absolute(file.path()));
		else if (isEqual&&difftime(decltype(ftime)::clock::to_time_t(ftime), SetTimeStamp::fetch()->getTime(criterium)) == 0)
			(*select) += new File(absolute(file.path()));
	}
	return select;
}

Selection* SelectNodeOperation::calculateAnd(SelectNode* left, SelectNode* right, string param, chars params) {
	Selection* leftOperand = selectFiles(param, params, left);
	Selection* rightOperand = selectFiles(param, params, right);

	Selection::SelElem *currentLeft = leftOperand->first, *currentPrevLeft = nullptr;
	while (currentLeft) {
		Selection::SelElem *currentRight = rightOperand->first;
		//search other selection
		for (; currentRight; currentRight = currentRight->next) {
			if ((*currentLeft->elem) == (*currentRight->elem)) break;
		}

		Selection::SelElem *old = currentLeft;
		currentLeft = currentLeft->next;
		if(currentRight==nullptr)//element is not in second selection
			if (currentPrevLeft == nullptr) {//element is first element in selection
				leftOperand->first = old->next;
				old->next = nullptr;
				delete old;
				old = nullptr;
			}
			else {//element not first element in selection
				currentPrevLeft->next = old->next;
				old->next = nullptr;
				delete old;
				old = nullptr;
			}
		if(old) currentPrevLeft = old;
	}

	rightOperand->deleteSelection();
	return leftOperand;
}
Selection* SelectNodeOperation::calculateOr(SelectNode* left, SelectNode* right, string param, chars params) {
	Selection* leftOperand = selectFiles(param, params, left);
	Selection* rightOperand = selectFiles(param, params, right);

	Selection::SelElem *currentLeft = leftOperand->first, *currentPrevLeft = nullptr;
	while (currentLeft) {
		Selection::SelElem *currentRight = rightOperand->first;
		//search other selection
		for (; currentRight; currentRight = currentRight->next) {
			if (*(currentLeft->elem) == *(currentRight->elem)) break;
		}

		if (currentRight == nullptr)//elemtn not found in second selection
			(*rightOperand) += currentLeft->elem;
		
		currentLeft = currentLeft->next;
	}

	leftOperand->deleteSelection();
	return rightOperand;
}
Selection* SelectNodeOperation::calculateXor(SelectNode* left, SelectNode* right, string param, chars params) {
	Selection* leftOperand = selectFiles(param, params, left);
	Selection* rightOperand = selectFiles(param, params, right);

	Selection* select = new Selection(param);
	Selection::SelElem *current = leftOperand->first;
	while (current) {
		Selection::SelElem *currentHelp = rightOperand->first;
		//search other selection
		for (; currentHelp; currentHelp = currentHelp->next) {
			if ((*current->elem) == (*currentHelp->elem)) break;
		}
		if (currentHelp == nullptr)//element is not in second, should be in XORselection
			(*select) += current->elem;

		current = current->next;
	}
	current = rightOperand->first;
	while (current) {
		Selection::SelElem *currentHelp = leftOperand->first;
		//search other selection
		for (; currentHelp; currentHelp = currentHelp->next) {
			if ((*current->elem) == (*currentHelp->elem)) break;
		}
		if (currentHelp == nullptr)//element is not in second, should be in XORselection
			(*select) += current->elem;

		current = current->next;
	}

	rightOperand->deleteSelection();
	leftOperand->deleteSelection();
	return select;
}
Selection* SelectNodeOperation::calculateNot(SelectNode* right, string param, chars params){
	Selection* select = new Selection(param);
	Selection* rightOperand = selectFiles(param, params, right);

	for (auto p : recursive_directory_iterator(current_path())) {
		File* file = new File(p.path());
		
		Selection::SelElem *current = rightOperand->first;
		for (; current; current = current->next)
			if ((current->elem) == file) break;
		//if element is not in selection, it should be in NOTselection
		if (current == nullptr) 
			(*select) += file;
	} 
	
	rightOperand->deleteSelection();
	return select;
}

Selection* SelectNode::selectFiles(string selectionName, chars params, SelectNode* node) {
	if (typeid(*node) == typeid(SelectNodeOperation))//calculate operation
		switch (((SelectNodeOperation*)node)->fetchOp()) {
		case SelectNodeOperation::AND: return ((SelectNodeOperation*)node)->calculateAnd(node->left,node->right, selectionName, params);
		case SelectNodeOperation::OR: return ((SelectNodeOperation*)node)->calculateOr(node->left, node->right, selectionName, params);
		case SelectNodeOperation::NOT: return ((SelectNodeOperation*)node)->calculateNot(node->right, selectionName, params);
		case SelectNodeOperation::XOR: return ((SelectNodeOperation*)node)->calculateXor(node->left, node->right, selectionName, params);
		}
	
	switch ((((SelectNodeCriterium*)node)->fetchCrit())[0]) {
	case 'n': {return selectName(selectionName, params, ((SelectNodeCriterium*)node)->fetchCrit()); }
	case 's': {return selectSize(selectionName, params, ((SelectNodeCriterium*)node)->fetchCrit()); }
	case 't': {return selectTime(selectionName, params, ((SelectNodeCriterium*)node)->fetchCrit()); }
	default:{
		throw NotExistingCriterium();
	}	//shoudl throw error
	}

	return nullptr;
}

SelectNode* Select::parseCriterium(string crit) {
	string criterium; char c;
	int length = crit.length();
	istringstream stream(crit);
	SelectNode* currentNode = nullptr, *root=nullptr;

	stream >> c;
	while (length--) {
		//end of the valid string
		//process it : either an operation(AND/OR/XOR/NOT) or a criterium name/size/timestamp
		switch (c) {
		case '(': {//end of operation
			SelectNode* newNode = new SelectNodeOperation(criterium,currentNode);
			if (root == nullptr) root = currentNode = newNode;
			else {
				if (currentNode->left == nullptr)currentNode->left = newNode;
				else currentNode->right = newNode;
			}
			currentNode = newNode;
			criterium = "";
			break;
		}
		case ')': {//end of parameter, right operand
			//go level up; 
			if (criterium == "")//extra ) 
				break;
			if (currentNode->right == nullptr) currentNode->right = new SelectNodeCriterium(criterium,currentNode);
			criterium = "";
			currentNode = currentNode->parent;
			break;
		}
		case ',': {//end of parameter, left operand
			//if left parameter exists, it was an operation, if not we need to add a criterium
			if (currentNode->left == nullptr) currentNode->left = new SelectNodeCriterium(criterium,currentNode);
			criterium = "";
			length--;//it doesnt read space
			break;
		}
		//case ' ': {break; }
		default: {//letter
			criterium += c;
			if (length == 0) {
				//last parameter
				SelectNode* newNode = new SelectNodeCriterium(criterium, currentNode);
				if (root == nullptr) root = newNode; //if there is no root, it is a simple selection, only one criterium
				/*else
					if (currentNode->left == nullptr)currentNode->left = newNode;
					else currentNode->right = newNode;*/
				break;
			}
		}
		}
		stream >> c;
	}

	return root;
}

void Select::run(chars& params, string param1, string param2) {
	SelectNode* selectionTree = parseCriterium(param2);

	Selection* select = selectionTree->selectFiles(param1, params, selectionTree);
	Selections::addSelection(select);
}
