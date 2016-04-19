#include "Copy.h"

Copy* Copy::copy = new Copy();

void Copy::aliasCheck(string *what, string *where) {
	//check if what file is an alias
	if (Aliases::fetchAliases()->fetchMap().count(*what))
		*what = Aliases::fetchAliases()->findObject(*what)->filePath().string();
	//check if where file is an alias
	if (Aliases::fetchAliases()->fetchMap().count(*where))
		*where = Aliases::fetchAliases()->findObject(*where)->filePath().string();
}

Selection* Copy::simbolicsNSelectionsCheck(string what) {
	Selection* select = nullptr;
	
	//check if the what name is a simbolic for a selection
	if ((Simbolics::fetchSimbolics()->fetchMap()).count(what))
		select = Simbolics::fetchSimbolics()->findObject(what);
	else if (Selections::isSelection(what))
		select = Selections::findSelection(what);

	return select;
}

void Copy::run(chars params, string param1, string param2) {
	path path1, path2; //path1 is what, path2 is where
	Selection* select = nullptr;
	
	//check for aliases
	aliasCheck(&param1, &param2);

	//check for selection
	//if a selection it has to be copied to a directory
	//-copy as 
	//copy filename to 'directory' + '/' + 'filename'
	//end copy
	select = simbolicsNSelectionsCheck(param1);
	if (select) {
		//selection to be copied
		select->copySelection(param2);
		return;
	}
	

	//fileWhat is a file what, fileWhere is a file where, final versions of files to be copied
	directory_entry fileWhat(param1), fileWhere(param2);

	//non existing file
	if (!exists(fileWhat)) {
		cout << "File you are trying to copy doesn't exist" << endl; return;
	}

	int i = 1;
	//destination directory exists
	if (exists(fileWhere)) {
		if (is_directory(fileWhere)) {
			//copying something to a directory
			string par = absolute(fileWhat.path()).string();
			directory_entry oldDir(current_path());
			current_path(fileWhere);
			if (!is_directory(par)) {
				//something is a file
				Copy::fetch()->run(params, par, fileWhat.path().filename().string());
			}
			else {
				//Something is a directory
				for (auto& p : directory_iterator(par)) {
					if (p != fileWhat) Copy::fetch()->run(params, p.path().string(), p.path().filename().string());
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

	//not existing directory where we are trying to copy a file 
	//cp x.gif Milan/x.gif		Milan/ doesn't exist
	//we make Milan directory
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