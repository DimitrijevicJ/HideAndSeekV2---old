#include "Help.h"

void Help::run(chars params, string param1, string param2) {
	if (param1 == "" || param1 == "mkdir") {
		cout << "MakeDirectory - mkdir" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "mkfile") {
		cout << "Make file - mkfile" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "cd") {
		cout << "ChangeDirectory - cd" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "dir") {
		cout << "PrintDirectoryContents - dir	[-a] [-p] [-s] [-d]" << endl << "     -a  :  All info" << endl << "     -p  :  Permissions" << endl << "     -s  :  Size" << endl << "     -d  :  Time and date" << endl << "     -ps, -pd, -sd  :  Any combination of two or three is possible, then will print all requested options" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "cp") {
		cout << "Copy - cp	[-d] [-r]" << endl << "     -d  :  Directories only" << endl << "     -r  :  Recursive, both directories and all their files" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "rm") {
		cout << "Delete - rm	[-a] [-f]" << endl << "     -a  :  Delete the file/directory with it's subdirectories" << endl << "    -f  :  Delete only the file/directory" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "mv") {
		cout << "Move - mv" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "sl") {
		cout << "Select - sl	[-p] [-f]" << endl << "     -p  :  Absolute path selection" << endl << "     -f  :  File name selection" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "as") {
		cout << "Assign - as	[-f] [-s]" << endl << "     -f  :  Alias for files/directories" << endl << "     -s  :  Simbolic name for selection of files/directories" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "h") {
		cout << "Help - h	[commandName]" << endl << "     commandName  :  Name of the command for which help is needed" << endl << endl;
		if (param1 != "") return;
	}
	if (param1 == "" || param1 == "q") {
		cout << "Exit - q" << endl << endl;
		if (param1 != "") return;
	}
}