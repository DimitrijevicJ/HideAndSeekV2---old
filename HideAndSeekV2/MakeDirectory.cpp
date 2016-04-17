#include "MakeDirectory.h"

MakeDirectory* MakeDirectory::makeDirectory = new MakeDirectory();

void MakeDirectory::run(chars params, string param1, string param2) {
	//mkdir directoryName

	//check if the parameters is an alias
	//if alias it will return a file with path
	//if not alias it will return nullptr then we use param1
	path pathh;
	if (Aliases::fetchAliases()->fetchMap().count(param1))
	{
		File* file = Aliases::fetchAliases()->findObject(param1);
		pathh = file->filePath();
	}
	else pathh = param1;
	if (exists(absolute((new File(pathh))->filePath()))) {
		cout << "That directory already exists" << endl;
		return;
	}
	if (!pathh.is_absolute()) pathh = current_path() /= pathh;
	if (create_directories(pathh)) { cout << "Created directory " << param1 << endl; }
	else { cout << "Directory couldn't be created" << endl; }
}