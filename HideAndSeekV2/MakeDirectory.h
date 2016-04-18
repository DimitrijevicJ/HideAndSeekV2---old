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


class MakeDirectory : public Command{
	static MakeDirectory* makeDirectory;
	MakeDirectory() = default;
	MakeDirectory(const MakeDirectory&) = delete;
	MakeDirectory& operator=(const MakeDirectory&) = delete;
public:
	static MakeDirectory* fetch() { return makeDirectory; }
	void run(chars params, string param1, string param2);
};

