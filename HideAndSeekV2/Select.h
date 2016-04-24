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
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

class Select : public Command{
	static Select* select;
	Select() = default;
	Select(const Select&) = delete;
	Select& operator=(const Select&) = delete;
public:
	static Select* fetch() { return select; }
	void run(chars& params, string param1, string param2);
	static void cleanUp() { delete select; select = nullptr; }
};
