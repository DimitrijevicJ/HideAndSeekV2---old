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

class MakeFile {
	static MakeFile* makeFile;
	MakeFile() = default;
	MakeFile(const MakeFile&) = delete;
	MakeFile& operator=(const MakeFile&) = delete;
public:
	static MakeFile* fetch() { return makeFile; }
	void run(chars params, string param1, string param2);
};

