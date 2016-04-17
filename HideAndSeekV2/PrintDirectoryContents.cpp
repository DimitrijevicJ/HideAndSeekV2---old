#include "PrintDirectoryContents.h"

PrintDirectoryContents* PrintDirectoryContents::printDirectoryContents = new PrintDirectoryContents();

void PrintDirectoryContents::run(chars params, string param1, string param2) {
	//dir -p ->permissions
	//dir -a ->all
	//dir -s ->size		//space(directoryname)
	//dir -d -> date
	//dir -ps ->permissions and size ... 
	int options = 0;
	for (char c : params) {
		switch (c)
		{
		case 'a': {options |= 0x7; break; }
		case 'p': {options |= 0x1; break; }
		case 's': {options |= 0x2; break; }
		case 'd': {options |= 0x4; break; }
		default: {throw new NonExistingOption(); }
		}
	}

	for (auto& p : directory_iterator(current_path()))
	{
		fileType(p.status());
		if (options & 1) {// permissions
			permissions(p.status());
		}
		if (options & 2) {//size
			struct stat filestatus;
			stat(p.path().string().c_str(), &filestatus);
			cout << setw(13);
			cout << filestatus.st_size << " B	";
		}
		if (options & 4) {//date
			auto ftime = last_write_time(p);
			time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
			string stream;
			stream = std::asctime(std::localtime(&cftime));
			stream.erase(stream.length() - 1, 1);
			cout << stream << "	";
		}
		cout << p.path().filename() << endl;
	}
}

void PrintDirectoryContents::permissions(file_status stat) {
	perms per = stat.permissions();

	cout << ((per & perms::owner_read) == perms::owner_read ? "r" : "-");
	cout << ((per & perms::owner_write) == perms::owner_write ? "w" : "-");
	cout << ((per & perms::owner_exec) == perms::owner_exec ? "x" : "-");
	cout << ((per & perms::group_read) == perms::group_read ? "r" : "-");
	cout << ((per & perms::group_write) == perms::group_write ? "w" : "-");
	cout << ((per & perms::group_exec) == perms::group_exec ? "x" : "-");
	cout << ((per & perms::others_read) == perms::others_read ? "r" : "-");
	cout << ((per & perms::others_write) == perms::others_write ? "w" : "-");
	cout << ((per & perms::others_exec) == perms::others_exec ? "x" : "-");
	cout << "	";
}
void PrintDirectoryContents::fileType(file_status stat) {
	cout << left << setw(7);
	if (is_regular_file(stat)) std::cout << "     ";
	if (is_directory(stat)) std::cout << "<DIR>";
}