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

#include "Info.h"
#include "SetTimeStamp.h"
#include "ColorMe.h"
#include "Aliases.h"
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

typedef vector<char> chars;

class Compare : public Command {
	static Compare* compare;
	Compare() = default;
	Compare(const Compare&) = delete;
	Compare& operator=(const Compare&) = delete;
public:
	int getPriviledge() override { return 1; }
	static Compare* fetch() { return compare; }
	void run(chars& params, string param1, string param2);
	static void cleanUp() { delete compare; compare = nullptr; }
};

