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

/*#include "ColorMe.h"
#include "Aliases.h"
#include "Assign.h"
#include "ChangeDirectory.h"
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
#include "Quit.h"*/

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

class Command {
public:
	virtual int getPriviledge() { return 0; }
	virtual ~Command() {}
	virtual void run(chars params, string param1, string param2) = 0;
	static void parseCommand(string command);
};

typedef unordered_map<string, Command*> mapsC;

class Commands {
	static Commands* commands;
	mapsC map;
	Commands() = default;
	Commands(const Commands&) = delete;
	Commands& operator=(const Commands&) = delete;
public:
	static Commands* fetch() { return commands; }
	mapsC& fetchMap() { return map; }
	static void cleanUp() { delete commands; commands = nullptr; }
};
