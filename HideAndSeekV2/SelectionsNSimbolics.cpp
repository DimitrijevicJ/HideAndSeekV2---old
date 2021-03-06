#include "SelectionsNSimbolics.h"

Selections::selectionsList* Selections::selections = nullptr;
Simbolics* Simbolics::SimbolicsMap = new Simbolics();

void Selection::operator+=(File* file) {
	SelElem* newE = new SelElem(file);
	if (first == nullptr) first = last = newE;
	else { last->next = newE; last = newE; }
}

void Selection::operator-=(File* file) {
	SelElem* curr = first, *prev = nullptr;
	while (curr) {
		if (*(curr->elem) == *file) break;
		prev = curr; curr = curr->next;
	}
	if (curr) {
		if (prev) prev->next = curr->next;
		else first = curr->next;
		delete curr->elem;
		delete curr;
	}
}

void Selection::deleteSelection() {
	SelElem* element;
	while (first) {
		element = first; element->next = nullptr;
		first = first->next;
		delete element->elem;
		delete element;
	}
	first = nullptr;
}

void Selection::copySelection(string where,chars params) {
	SelElem* current = first;
	while (current) {
		if (params.size() == 0) { params.resize(1); params[0] = 'r'; }
		Copy::fetch()->run(params, current->elem->filePath().string(), where+"/"+current->elem->filePath().filename().string());
		current = current->next;
	}
}


Selection* Selections::findSelection(string sl) {
	selectionsList* current = selections;
	while (current) {
		if (current->selection->fetchName() == sl) break;
		current = current->next;
	}
	if (current == nullptr) return nullptr;
	return current->selection;
}

void Selections::removeSelection(string sl) {
	selectionsList* current = selections, *previous = nullptr;
	while (current) {
		if (current->selection->fetchName() == sl) break;
		previous = current;
		current = current->next;
	}
	if (previous)previous->next = current->next;
	else selections = current->next;
	current->selection->deleteSelection();
	delete current->selection;
	delete current;
}

void Selections::saveSelections(path pathh) {
	selectionsList* current = selections;
	fstream file;
	chars params(0);
	MakeFile::fetch()->run(params, pathh.string(), "");
	file.open(pathh.string().c_str(), std::fstream::out);
	while (current)
	{
		file << "*" << current->selection->name << "\n";
		Selection::SelElem* elem = current->selection->first;
		while (elem) {
			file << "~" << elem->elem->filePath() << "\n";
			elem = elem->next;
		}
		current = current->next;
	}
	file.close();
}

void Selections::loadSelections(path pathh) {
	fstream file;
	file.open(pathh.string().c_str(), std::fstream::in);
	string word, selectionName;
	Selection* selection = nullptr;
	getline(file, word);
	while (word != "")
	{
		if (word[0] == '*') {
			selectionName = word.erase(0, 1);
			if (Simbolics::fetchSimbolics()->findObject(selectionName) == nullptr)
				Selections::addSelection(new Selection(selectionName));
		}
		else {
			word.erase(0, 1);
			selection = Selections::findSelection(selectionName);
			if(exists(word)) (*selection) += new File(word);
		}
		getline(file, word);
	}
	file.close();
}

bool Selections::isSelection(string selection) {
	selectionsList* current = selections;
	for (; current; current = current->next) if (current->selection->fetchName() == selection) return true;
	return false;
}


Selection* Simbolics::findObject(string al){ 
	if (map.count(al) == 0) return nullptr; 
	return fetchMap().at(al); 
} //catch exception

void Simbolics::removeSimbolic(string al) { map.erase(al); }

void Simbolics::loadSimbolic(path pathh) {
	fstream file;
	file.open(pathh.string().c_str(), std::fstream::in);
	int word = 1;
	string readWord, simbolicName, selectionName;
	while (file >> readWord) {
		if (word == 1) {
			simbolicName = readWord;
			word = 2;
		}
		else {
			selectionName = readWord;
			word = 2;
			Selection* selection = new Selection(selectionName);
			Selections::addSelection(selection);
			map.insert({ simbolicName, selection });
		}
	}
	file.close();
}

void Simbolics::saveASimbolic(path pathh) {
	fstream file;
	chars params(0);
	MakeFile::fetch()->run(params, pathh.string(), "");
	file.open(pathh.string().c_str(), std::fstream::out);
	for (auto& a : map) {
		file << a.first << " " << a.second->fetchName() << "\n";
	}
	file.close();
}