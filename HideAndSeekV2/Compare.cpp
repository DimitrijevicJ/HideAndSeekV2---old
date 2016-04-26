#include "Compare.h"

Compare* Compare::compare = new Compare();
void parse(string s, string& s1, string& s2, string& what, string& criteriums) {
	char c;
	while ((c = s[0]) != ' ') {
		s1 += c;
		s.erase(0, 1);
	}
	while ((c = s[0]) != ' ') {
		what += c;
		s.erase(0, 1);
	}
	while ((c = s[0]) != ' ') {
		s2 += c;
		s.erase(0, 1);
	}
	s.erase(0, 3);
	criteriums = s;
}

class Selection;

Selection* UNION(string name, string s1Name, string s2Name, int* criteriums) {
	Selection* select = new Selection(name);
	
	Selection* sel1 = Selections::findSelection(s1Name), *sel2 = Selections::findSelection(s2Name);
	Selection::SelElem *currentLeft = sel1->first, *currentPrevLeft = nullptr;
	while (currentLeft) {
		Selection::SelElem *currentRight = sel2->first;
		//search other selection
		for (; currentRight; currentRight = currentRight->next) {
			bool name = criteriums[0] == 0 || (criteriums[0] == 1 && (currentLeft->elem->fileNames() == currentRight->elem->fileNames()));
			bool size = criteriums[1] == 0 || (criteriums[1] == 1 && (PrintDirectoryContents::fetch()->fileSize(currentLeft->elem->filePath()) == PrintDirectoryContents::fetch()->fileSize(currentRight->elem->filePath())));
			bool time = criteriums[2] == 0 || (criteriums[2] == 1 && (last_write_time(currentLeft->elem->filePath()) == last_write_time(currentRight->elem->filePath())));
			if (name&&size&&time) break;
		}

		if (currentRight == nullptr)//elemtn not found in second selection
			(*select) += currentLeft->elem;

		currentLeft = currentLeft->next;
	}
	currentLeft = sel2->first;
	for (; currentLeft; currentLeft = currentLeft->next) (*select) += currentLeft->elem;

	return select;
}


Selection* INTERSECTION(string name, string s1Name, string s2Name, int* criteriums) {
	Selection* select = new Selection(name);

	Selection* sel1 = Selections::findSelection(s1Name), *sel2 = Selections::findSelection(s2Name);
	Selection::SelElem *currentLeft = sel1->first, *currentPrevLeft = nullptr;
	while (currentLeft) {
		Selection::SelElem *currentRight = sel2->first;
		//search other selection
		for (; currentRight; currentRight = currentRight->next) {
			bool name = criteriums[0] == 0 || (criteriums[0] == 1 && (currentLeft->elem->fileNames() == currentRight->elem->fileNames()));
			bool size = criteriums[1] == 0 || (criteriums[1] == 1 && (PrintDirectoryContents::fetch()->fileSize(currentLeft->elem->filePath()) == PrintDirectoryContents::fetch()->fileSize(currentRight->elem->filePath())));
			bool time = criteriums[2] == 0 || (criteriums[2] == 1 && (last_write_time(currentLeft->elem->filePath()) == last_write_time(currentRight->elem->filePath())));
			if (name&&size&&time) break;
		}

		if (currentRight != nullptr)//elemtn found in second selection
			(*select) += currentLeft->elem;

		currentLeft = currentLeft->next;
	}

	return select;
}


Selection* DIFFERENTE(string name, string s1Name, string s2Name, int* criteriums) {
	Selection* select = new Selection(name);

	Selection* sel1 = Selections::findSelection(s1Name), *sel2 = Selections::findSelection(s2Name);
	Selection::SelElem *currentLeft = sel1->first, *currentPrevLeft = nullptr;
	while (currentLeft) {
		Selection::SelElem *currentRight = sel2->first;
		//search other selection
		for (; currentRight; currentRight = currentRight->next) {
			bool name = criteriums[0] == 0 || (criteriums[0] == 1 && (currentLeft->elem->fileNames() == currentRight->elem->fileNames()));
			bool size = criteriums[1] == 0 || (criteriums[1] == 1 && (PrintDirectoryContents::fetch()->fileSize(currentLeft->elem->filePath()) == PrintDirectoryContents::fetch()->fileSize(currentRight->elem->filePath())));
			bool time = criteriums[2] == 0 || (criteriums[2] == 1 && (last_write_time(currentLeft->elem->filePath()) == last_write_time(currentRight->elem->filePath())));
			if (name&&size&&time) break;
		}

		if (currentRight == nullptr)//elemt not found in second selection
			(*select) += currentLeft->elem;

		currentLeft = currentLeft->next;
	}

	return select;
}

void Compare::run(chars& params, string param1, string param2) {
	string s1Name = "", s2Name = "", what = "", criteriums = "";
	Selection* newSelection = new Selection(param1);
	parse(param2, s1Name, s2Name, what, criteriums);

	istringstream crit(criteriums);
	string word;
	int criteriumss[] = { 0,0,0 };	//name, size, time
	while (crit >> word) {
		if (word == "name") criteriumss[0] = 1;
		if (word == "size") criteriumss[1] = 1;
		if (word == "time") criteriumss[2] = 1;
	}

	switch (what[0]) {
	case 'u': {Selections::addSelection(UNION(param1, s1Name, s2Name, criteriumss)); break; }
	case 'i': {Selections::addSelection(INTERSECTION(param1, s1Name, s2Name, criteriumss)); break; }
	case 'd': {Selections::addSelection(DIFFERENTE(param1, s1Name, s2Name, criteriumss)); break; }
	}
}