#include "MakeFile.h"

void MakeFile::run(chars params, string param1, string param2) {
	//mkdir directoryName
	path pathh;
	if (Aliases::fetchAliases()->fetchMap().count(param1))
	{
		File* file = Aliases::fetchAliases()->findObject(param1);
		pathh = file->filePath();
	}
	else pathh = param1;
	if (!exists(absolute((new File(pathh.parent_path()))->filePath()))) {
		(new MakeDirectory())->run(params, pathh.parent_path().string(), param2);
	}
	if (exists(pathh)) {
		cout << "There already exists a file with such name. Please choose another" << endl; return;
	}
	ofstream ofstr(pathh);
	cout << "Created file " << param1 << endl;
}