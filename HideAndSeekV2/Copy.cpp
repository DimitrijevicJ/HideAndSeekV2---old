#include "Copy.h"

Copy* Copy::copy = new Copy();

void Copy::run(chars params, string param1, string param2) {
	path path1, path2; //path1 is what, path2 is where
	int is_simbolic = 0;
	Selection* select = nullptr;
	if (Aliases::fetchAliases()->fetchMap().count(param1))
	{
		File* file = Aliases::fetchAliases()->findObject(param1);
		path1 = file->filePath();
	}
	else path1 = param1;
	if ((Simbolics::fetchSimbolics()->fetchMap()).count(param1)) {
		//param1 is a simbolic name, we need to copy a selection
		is_simbolic = 1;
		select = Simbolics::fetchSimbolics()->findObject(param1);
	}
	if (Aliases::fetchAliases()->fetchMap().count(param2))
	{
		File* file = Aliases::fetchAliases()->findObject(param2);
		path2 = file->filePath();
	}
	else path2 = param2;
	if (is_simbolic || Selections::isSelection(param1)) {
		if (select == nullptr) select = Selections::findSelection(param1);
		directory_entry oldDir(current_path());
		current_path(param2);
		select->copySelection();
		current_path(oldDir);
		return;
	}
	directory_entry fileWhat(path1), fileWhere(path2);

	if (!exists(fileWhat)) {
		cout << "File you are trying to copy doesn't exist" << endl; return;
	}
	int i = 1;
	//destination directory exists
	if (exists(fileWhere)) {
		if (is_directory(fileWhere)) {
			string par = absolute(fileWhat.path()).string();
			directory_entry oldDir(current_path());
			current_path(fileWhere);
			if (!is_directory(par)) {
				(new Copy())->run(params, par, fileWhat.path().filename().string());
			}
			else {
				for (auto& p : directory_iterator(par)) {
					if (p != fileWhat) (new Copy())->run(params, p.path().string(), p.path().filename().string());
				}
			}
			current_path(oldDir);
			return;
		}
		else {
			while (exists(fileWhere))
			{
				char buffer[10];
				_itoa(i++, buffer, 10);
				param2.insert(param2.find_last_of('.'), buffer);
				if (Aliases::fetchAliases()->fetchMap().count(param2))
				{
					File* file = Aliases::fetchAliases()->findObject(param2);
					path2 = file->filePath();
				}
				else path2 = param2;
				fileWhere.assign(path2);
			}
		}
	}
	if (!exists(absolute(fileWhere.path().parent_path()))) {
		MakeDirectory::fetch()->run(params, fileWhere.path().parent_path().string(), param2);
	}
	if (params.size() > 0 && params[0] == 'd') {
		std::experimental::filesystem::copy(fileWhat, fileWhere, copy_options::directories_only);
		int countCopied = 1;
		for (auto p : directory_iterator(fileWhere)) { countCopied++; }
		cout << "Files copied : " << countCopied << endl;
		return;
	}
	else if (params.size() == 0 || params[0] == 'r') {
		std::experimental::filesystem::copy(fileWhat, fileWhere, copy_options::recursive);
		int countCopied = 1;
		for (auto p : recursive_directory_iterator(fileWhere)) { countCopied++; }
		if (movee) cout << "Files moved : " << countCopied << endl;
		else cout << "Files copied : " << countCopied << endl;
		return;
	}
	else throw new NonExistingOption();
}