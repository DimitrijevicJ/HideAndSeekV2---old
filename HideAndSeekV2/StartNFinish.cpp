#include "StartNFinish.h"

void addCommands() {
	Commands::fetch()->fetchMap().insert({ "mkfile", MakeFile::fetch() });
	Commands::fetch()->fetchMap().insert({ "mkdir", MakeDirectory::fetch() });
	Commands::fetch()->fetchMap().insert({ "mkfile", MakeFile::fetch() });
	Commands::fetch()->fetchMap().insert({ "as", Assign::fetch() });
	Commands::fetch()->fetchMap().insert({ "cd", ChangeDirectory::fetch() });
	Commands::fetch()->fetchMap().insert({ "cp", Copy::fetch() });
	Commands::fetch()->fetchMap().insert({ "rm", Delete::fetch() });
	Commands::fetch()->fetchMap().insert({ "h", Help::fetch() });
	Commands::fetch()->fetchMap().insert({ "mv", Move::fetch() });
	Commands::fetch()->fetchMap().insert({ "dir", PrintDirectoryContents::fetch() });
	Commands::fetch()->fetchMap().insert({ "sl", Select::fetch() });
	Commands::fetch()->fetchMap().insert({ "q", Quit::fetch() });
}

void start() {
	addCommands();

	colorMe(COLOR_SILVER);
	cout << "Do you have any simbolic names and selections you would like to load? (YES/NO)" << endl;
	string answer;
	cin >> answer;
	if (answer == "YES" || answer == "yes" || answer == "Yes") {
		cout << "Where have you saved your simbolics?" << endl;
		cin >> answer;
		path pathSimbolics = answer;
		if (!exists(pathSimbolics)) cout << "File couldn't be found." << endl;
		Simbolics::fetchSimbolics()->loadSimbolic(pathSimbolics);

		cout << "Where have you saved your selections?" << endl;
		cin >> answer;
		path pathSelections = answer;
		if (!exists(pathSelections)) cout << "File couldn't be found." << endl;
		Selections::loadSelections(pathSelections);
	}
	cout << "Do you have any aliases you would like to load? (YES/NO)" << endl;
	cin >> answer;
	if (answer == "YES" || answer == "yes" || answer == "Yes") {
		cout << "Where have you saved your aliases?" << endl;
		cin >> answer;
		path pathAliases = answer;
		if (!exists(pathAliases)) cout << "File couldn't be found." << endl;
		Aliases::fetchAliases()->loadAlias(pathAliases);
	}
	cin.ignore();
}

void freeMemory() {
	Aliases::cleanUp();
	Assign::cleanUp();
	ChangeDirectory::cleanUp();
	Copy::cleanUp();
	Delete::cleanUp();
	Help::cleanUp();
	MakeDirectory::cleanUp();
	MakeFile::cleanUp();
	Move::cleanUp();
	PrintDirectoryContents::cleanUp();
	Quit::cleanUp();
	Select::cleanUp();
	Simbolics::cleanUp();

	User::cleanUp();
}

void end() {
	colorMe(COLOR_SILVER);
	cout << "Would you like to save your simbolics and selections?" << endl;
	string answer;
	cin >> answer;
	if (answer == "YES" || answer == "yes" || answer == "Yes") {
		cout << "Where would you like to save your simbolics?" << endl;
		cin >> answer;
		path pathSelections = answer;
		Simbolics::fetchSimbolics()->saveASimbolic(pathSelections);
		cout << "Where would you like to save your selections?" << endl;
		cin >> answer;
		pathSelections = answer;
		Selections::saveSelections(pathSelections);
	}
	cout << "Would you like to save your Aliases?" << endl;
	cin >> answer;
	if (answer == "YES" || answer == "yes" || answer == "Yes") {
		cout << "Where would you like to save your aliases?" << endl;
		cin >> answer;
		path pathSelections = answer;
		Aliases::fetchAliases()->saveAlias(pathSelections);
	}
	
	freeMemory();
	exit(0);
}