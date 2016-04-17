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
#include "Move.h"
#include "PrintDirectoryContents.h"
#include "Select.h"
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

extern int movee;

class Delete {
	static Delete* deletee;
	Delete() = default;
	Delete(const Delete&) = delete;
	Delete& operator=(const Delete&) = delete;
public:
	static Delete* fetch() { return deletee; }
	void run(chars params, string param1, string param2);
};

