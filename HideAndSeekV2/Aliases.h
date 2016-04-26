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

#include "Compare.h"
#include "Info.h"
#include "SetTimeStamp.h"
#include "ColorMe.h"
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
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef unordered_map<string, File*> mapsA;

class Aliases {
	static Aliases* AliasesMap;
	mapsA map;
public:
	static Aliases* fetchAliases() { return AliasesMap; }
	mapsA& fetchMap() { return map; }
	void addAlias(string alias, File* object);
	File* findObject(string al);
	void removeAlias(string al) { map.erase(al); }
	void loadAlias(path pathh);
	void saveAlias(path pathh);
	static void cleanUp() { delete AliasesMap; AliasesMap = nullptr; }
};
