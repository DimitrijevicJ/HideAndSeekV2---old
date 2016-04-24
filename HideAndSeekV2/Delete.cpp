#include "Delete.h"

Delete* Delete::deletee = new Delete();

void Delete::run(chars& params, string param1, string param2) {

	directory_entry file(param1);
	if (!exists(file)) {
		cout << "File doesn't exist" << endl; return;
	}

	if (file.path() == current_path()) {
		colorMe(COLOR_FUCHSIA);
		cout << "You can't delete current directory." << endl;
		colorMe(COLOR_SILVER);
		return;
	}
	if (!movee) {
		cout << "Are you sure you want to delete those files?" << endl;
		string answer;
		cin >> answer;
		if (answer == "no" || answer == "NO" || answer == "No") return;
	}
	std::uintmax_t deletedFiles = 1;
	if (params.size()>0 && params[0] == 'a') deletedFiles = remove_all(file);
	else
		if (params.size() == 0 || params[0] == 'f') {
			try {
				deletedFiles = remove(file);
			}
			catch (...) {
				string answer;
				cout << "That directory is not empty. If you want to delete it anyway, write force" << endl;
				cin >> answer;
				if (answer == "force" || answer == "FORCE" || answer == "Force") remove_all(file);
			}
		}
		else throw NonExistingOption();
		if (!movee) cout << "Deleted the file." << endl;
}