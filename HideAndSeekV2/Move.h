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
#include "PrintDirectoryContents.h"
#include "Select.h"
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

//As move option has been implemented as copy+delete, there has to be a way to tell copy and delete commands that they are moving
//int movee=0;

class Move : public Command {
	static Move* move;
	Move() = default;
	Move(const Move&) = delete;
	Move& operator=(const Move&) = delete;
public:
	static Move* fetch() { return move; }
	void run(chars params, string param1, string param2);
	static void cleanUp() { delete move; move = nullptr; }
};
