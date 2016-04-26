#include "Command.h"
#include "ColorMe.h"
#include "Aliases.h"
#include "Assign.h"
#include "ChangeDirectory.h"
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
#include "SetTimeStamp.h"

Commands* Commands::commands = new Commands();

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
			else param2 += word+" ";
		}
	}
	if(param2!="") param2.erase(param2.length() - 1, 1);
	params.resize(numParams);

	if (Commands::fetch()->fetchMap().count(com)==0) {
		if (com == "") return;
		throw NonExistingCommand();
	}
	else {

		Command* comm = Commands::fetch()->fetchMap().at(com);
		if(User::fetchUser()->fetchMode()==0 || (comm->getPriviledge()==User::fetchUser()->fetchMode())) comm->run(params, param1, param2);
		else cout << "You don't have priviledges to execute that command." << endl;
		return;
	}
}