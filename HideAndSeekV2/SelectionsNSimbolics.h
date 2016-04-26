#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <filesystem>
#include <experimental/filesystem>
#include <bitset>
#include <vector>
#include <unordered_map>

#include "SetTimeStamp.h"
#include "ColorMe.h"
#include "Aliases.h"
#include "Assign.h"
#include "ChangeDirectory.h"
#include "Command.h"
#include "Copy.h"
#include "Exceptions.h"
#include "Help.h"
#include "MakeDirectory.h"
#include "MakeFile.h"
#include "Delete.h"
#include "Move.h"
#include "PrintDirectoryContents.h"
#include "Select.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;


class Selection {
public:
	struct SelElem {
		File* elem;
		SelElem* next;
		SelElem(File* e) { elem = e; next = nullptr; }
	};
	string name;
	SelElem* first, *last;
	Selection(string name) : name(name) { first = last = nullptr; }
	void operator+=(File* file);
	void operator-=(File* file);
	void deleteSelection();
	string fetchName() const { return name; }
	void copySelection(string,chars);
};

class Selections {
public:
	struct selectionsList {
		Selection* selection;
		selectionsList* next;
		selectionsList(Selection* s) { selection = s; next = nullptr; }
	};
	static selectionsList* selections;
	static void addSelection(Selection* a) { selectionsList* elem = new selectionsList(a); elem->next = selections; selections = elem; }
	static Selection* findSelection(string sl);
	static void removeSelection(string sl);
	static void saveSelections(path pathh);
	static void loadSelections(path pathh);
	static bool isSelection(string selection);
};

typedef unordered_map<string, Selection*> mapsS;

class Simbolics{
	mapsS map;
	static Simbolics* SimbolicsMap;
	Simbolics() = default;
	Simbolics(const Simbolics&) = delete;
	Simbolics& operator=(const Simbolics&) = delete;
public:
	void addSimb(string sim, Selection* sel) { if (sel) map.insert({ sim, sel }); }
	static Simbolics* fetchSimbolics() { return SimbolicsMap; }
	mapsS fetchMap() { return map; }
	Selection* findObject(string al); 
	void removeSimbolic(string al);
	void loadSimbolic(path pathh);
	void saveASimbolic(path pathh);
	static void cleanUp() { delete SimbolicsMap; SimbolicsMap = nullptr; }
};
