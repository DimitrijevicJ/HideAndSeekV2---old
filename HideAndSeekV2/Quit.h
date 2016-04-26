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
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

class Quit : public Command {
	static Quit* quit;
	Quit() = default;
	Quit(const Quit&) = delete;
	Quit operator=(const Quit&) = delete;
public:
	int getPriviledge() override { return 1; }
	static Quit* fetch() { return quit; }
	void run(chars& params, string param1, string param2);
	static void cleanUp() { delete quit; quit = nullptr; }
};