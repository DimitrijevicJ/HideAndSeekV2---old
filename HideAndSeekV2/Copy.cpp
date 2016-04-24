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

void Copy::copyDirectory(string what, string where, chars& params) {
	//don't like it fix it
	int countCopied = 1;
	if (params.size()==0 || (params.size()==1 && params[0] == 'd')) {
		//NO std::experimental::filesystem::copy(what, where, copy_options::directories_only);
		for (auto p : recursive_directory_iterator(what)) { 
			if (is_directory(p)) Copy::run(params, absolute(p).string(), where);
			countCopied++; 
		}
	}
	else if (params.size()==1 &&  params[0] == 'r') {
		//std::experimental::filesystem::copy(what, where, copy_options::recursive);
		for (auto p : recursive_directory_iterator(what)) { 
			run(params, absolute(p).string(), where);
			countCopied++; 
		}
	}
	else throw NonExistingOption();

	if (movee) cout << "Files moved : " << countCopied << endl;
	else cout << "Files copied : " << countCopied << endl;
	return;
}

void Copy::run(chars& params, string param1, string param2) {
	path path1, path2; //path1 is what, path2 is where
	Selection* select = nullptr;

	if (param2 == ""||param1=="") throw MissingOperands();
	
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
		select->copySelection(param2,params);
		return;
	}
	

	//fileWhat is a file what, fileWhere is a file where, final versions of files to be copied
	directory_entry fileWhat(param1), fileWhere(param2);

	//non existing file
	if (!exists(fileWhat)) {
		cout << "File you are trying to copy doesn't exist" << endl; return;
	}

	//not existing directory where we are trying to copy a file 
	//cp x.gif Milan/x.gif		Milan/ doesn't exist
	//we make Milan directory
	if (!exists(absolute(fileWhere.path().parent_path()))) {
		MakeDirectory::fetch()->run(params, fileWhere.path().parent_path().string(), param2);
	}

	if (exists(fileWhere)&&is_directory(fileWhere)) {
		//->directory
		string rootToCopy = absolute(fileWhere).string() + '/';
		if (!is_directory(fileWhat)) {
			//file->directory
			std::experimental::filesystem::copy(fileWhat, rootToCopy+fileWhat.path().filename().string());
		}
		else {
			//directory->directory
			//copying directory contents to another directory
			directory_entry fileWhat(fileWhat);
			string where = fileWhere.path().string().append("/" + fileWhat.path().filename().string());
			MakeDirectory::fetch()->run(params, where, "");
			copyDirectory(fileWhat.path().string(), where, params);
		}
	}
	else if (!exists(fileWhere)) {
		if (is_directory(fileWhat))
		{
			//directory->
			string where = fileWhere.path().string();
			MakeDirectory::fetch()->run(params, where, "");
			copyDirectory(fileWhat.path().string(), where, params);
		}
		else {
			//file->
			std::experimental::filesystem::copy(fileWhat, fileWhere);
			std::cout<<"Files copied : 1"<<endl;
		}
	}
	else if (!is_directory(fileWhere)) {
		//directory->file
		if (is_directory(fileWhat)) throw CopyDirectoryToFileError();
		else {
			//file->file
			if (exists(fileWhere)) {
				if (params.size() == 1||params.size()==0) {
					printCopyOptions();
fail:					char answer;
					cin >> answer;
					switch (answer) {
					case 'Y': {
						std::experimental::filesystem::copy(fileWhat, fileWhere,copy_options::overwrite_existing);
						std::cout << "Files copied : 1" << endl; break;
					}
					case 'A': {
						std::experimental::filesystem::copy(fileWhat, fileWhere,copy_options::overwrite_existing);
						std::cout << "Files copied : 1" << endl;
						params.resize(2, 'A');
						if (params[0] == 'A') params[0] = 'd'; break;
					}
					case 'S': {break; }
					case 'K': {params.resize(2, 'K'); if (params[0] == 'K') params[0] = 'd'; break; }
					case 'B': {throw AbortCopyCommand(); }
					default: {cout << "Error. Please try again.\n"; goto fail; }
					}
				}
				else //already known decision
				{
					if (params.size() == 2 && params[1] == 'A') {
						std::experimental::filesystem::copy(fileWhat, fileWhere,copy_options::overwrite_existing);
						std::cout << "Files copied : 1" << endl;
					}
				}
			}
		}
	}
}

void Copy::printCopyOptions() {
	cout << "Yes - Y\nYes All - A\nSkip - S\nSkip All - K\nAbort - B\n";
}