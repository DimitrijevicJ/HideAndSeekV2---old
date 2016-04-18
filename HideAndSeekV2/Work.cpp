#include <iostream>
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
#include "Select.h"
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"
#include "User.h"

using namespace std;
using namespace std::experimental::filesystem;

int main(int argc, char* argv[])
{
	if (argc == 2) {
		if (string(argv[1]) == "password") User::fetchUser()->changeUserMode();
	}
	
	start();
	while (1) {
		try {
			colorMe(COLOR_LIME);
			cout << current_path() << " : ";
			colorMe(COLOR_YELLOW);
			string command;
			getline(cin, command);
			Command::parseCommand(command);
		}
		catch (exception& except) {
			colorMe(COLOR_FUCHSIA);
			cout << except.what() << endl;
		}
		catch (...) {
			exit(7);
		}
	}

}