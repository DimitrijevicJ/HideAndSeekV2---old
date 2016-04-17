#include "ChangeDirectory.h"

void ChangeDirectory::run(chars params, string param1, string param2) {
		path pathh;
		if (Aliases::fetchAliases()->fetchMap().count(param1))
		{
			File* file = Aliases::fetchAliases()->findObject(param1);
			pathh = file->filePath();
		}
		else pathh = param1;
		if (param1 == "C:/") { current_path("C:/"); return; }
		if (!exists(absolute((new File(pathh.parent_path()))->filePath()))) { cout << "No such directory." << endl; return; }
		if (!is_directory(pathh)) { cout << "Not a directory." << endl; return; }
		if (param1 == "..") pathh = current_path().parent_path();
		current_path(pathh);
	}
