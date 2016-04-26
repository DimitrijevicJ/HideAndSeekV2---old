#include "Info.h"

Info* Info::info = new Info();

void Info::run(chars& params, string param1, string param2) {
	for (char c = 'A'; c <= 'Z'; c++) {
		string pathh = ""; pathh += c; pathh += ':'; pathh +='/';
		space_info space = std::experimental::filesystem::space(pathh);
		if (exists(path(pathh)))
			std::cout << pathh << "	" << "Capacity: " << space.capacity << "B     Free: " << space.free << "B     Available: " << space.available << 'B'<<endl;
	}
}