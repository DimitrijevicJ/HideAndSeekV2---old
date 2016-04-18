#include "StartNFinish.h"

void start() {
	unordered_map<string, Command*> mapa;
	mapa.insert({"mkfile", MakeFile::fetch()});
	mapa.insert({ "mkdir", MakeDirectory::fetch() });
	mapa.insert({ "mkfile", MakeFile::fetch() });
	mapa.insert({ "as", Assign::fetch() });
	mapa.insert({ "cd", ChangeDirectory::fetch() });
	mapa.insert({ "cp", Copy::fetch() });
	mapa.insert({ "rm", Delete::fetch() });
	mapa.insert({ "h", Help::fetch() });
	mapa.insert({ "mv", Move::fetch() });
	mapa.insert({ "dir", PrintDirectoryContents::fetch() });
	mapa.insert({ "sl", Select::fetch() });

	Commands::fetch()->fetchMap() = mapa;
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

	exit(0);
}