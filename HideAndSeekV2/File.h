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
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;

class File {
	path directory;
	path fileName;
public:
	File(string ss) { path h = ss; directory = absolute(h.parent_path()); fileName = h.filename(); }
	File(path pathh) { directory = absolute(pathh.parent_path()); fileName = pathh.filename(); }
	File(const File& file) { directory = file.directory; fileName = file.fileName; }

	bool operator==(File file2) { return directory == file2.directory&&fileName == file2.directory; }
	path filePath() const { return directory / fileName; }
};
