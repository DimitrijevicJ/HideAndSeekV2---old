#include "Command.h"

void Command::parseCommand(string command) {
	istringstream parser(command);
	string com, word; parser >> com;
	chars params(4);
	string param1 = "", param2 = ""; int numParams = 0;
	while (parser >> word) {
		if (word[0] == '-') {
			word.erase(0, 1);
			unsigned int i = 0;
			while (i < (int)word.length()) params[numParams++] = word[i++];
		}
		else {
			if (param1 == "") param1 = word;
			else param2 = word;
		}
	}
	params.resize(numParams);
	if (com == "MakeDirectory" || com == "mkdir") { MakeDirectory::fetch()->run(params, param1, param2); return; }
	else if (com == "MakeFile" || com == "mkfile") { MakeFile::fetch()->run(params, param1, param2); return; }
	else if (com == "ChangeDirectory" || com == "cd") { ChangeDirectory::fetch()->run(params, param1, param2); return; }
	else if (com == "PrintDirectoryContents" || com == "dir") { PrintDirectoryContents::fetch()->run(params, param1, param2); return; }
	else if (com == "Copy" || com == "cp") { Copy::fetch()->run(params, param1, param2); return; }
	else if (com == "Delete" || com == "rm") { Delete::fetch()->run(params, param1, param2); return; }
	else if (com == "Move" || com == "mv") { Move::fetch()->run(params, param1, param2); return; }
	else if (com == "Select" || com == "sl") { Select::fetch()->run(params, param1, param2); return; }
	else if (com == "Assign" || com == "as") { Assign::fetch()->run(params, param1, param2); return; }
	else if (com == "Help" || com == "h") { Help::fetch()->run(params, param1, param2); return; }
	else if (com == "Exit" || com == "q") end();
	else if (com == "") return;
	else throw new NonExistingCommand();
}