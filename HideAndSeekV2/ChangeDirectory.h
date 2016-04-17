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

class ChangeDirectory {
	static ChangeDirectory* changeDirectory;
	ChangeDirectory() = default;
	ChangeDirectory(const ChangeDirectory&) = delete;
	ChangeDirectory& operator=(const ChangeDirectory&) = delete;
public:
	static ChangeDirectory* fetch() { return changeDirectory; }
	void run(chars params, string param1, string param2);
};