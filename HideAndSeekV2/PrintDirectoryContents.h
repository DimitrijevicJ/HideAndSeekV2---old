#pragma once

#include <iostream>
#include <iomanip>
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
#include "Select.h"
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

class PrintDirectoryContents : public Command{
	static PrintDirectoryContents* printDirectoryContents;
	PrintDirectoryContents() = default;
	PrintDirectoryContents(const PrintDirectoryContents&) = delete;
	PrintDirectoryContents& operator=(const PrintDirectoryContents&) = delete;
public:
	int getPriviledge() override { return 1; }
	static PrintDirectoryContents* fetch() { return printDirectoryContents; }
	void run(chars params, string param1, string param2);
private:
	void permissions(file_status stat);
	void fileType(file_status stat);
};
