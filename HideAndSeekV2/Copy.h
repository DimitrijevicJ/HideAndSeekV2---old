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

typedef vector<char> chars;

extern int movee;

class Selection;

class Copy : public Command {
	static Copy* copy;
	Copy() = default;
	Copy(const Copy&) = delete;
	Copy& operator=(const Copy&) = delete;
	
	void aliasCheck(string*, string*);
	Selection* simbolicsNSelectionsCheck(string);
	void copyDirectory(string, string, chars&);
	void printCopyOptions();
public:
	static Copy* fetch() { return copy; }
	void run(chars& params, string param1, string param2);
	static void cleanUp() { delete copy; copy = nullptr; }
};


