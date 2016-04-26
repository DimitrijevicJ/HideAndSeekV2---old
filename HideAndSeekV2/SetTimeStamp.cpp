#include "SetTimeStamp.h"

SetTimeStamp* SetTimeStamp::setTimeStamp = new SetTimeStamp();

bool match(char* first, char* second);

time_t SetTimeStamp::getTime(string t){
	if(t=="now") return time(0);

	struct tm* rawTime = new struct tm();
	int day, month, year, hour, minute, second;
	if (t.length() <= 11) {
		sscanf(t.c_str(), "%d.%d.%d.", &day, &month, &year);
		rawTime->tm_year = year-1900;
		rawTime->tm_mon = month - 1;
		rawTime->tm_mday = day;
		rawTime->tm_hour = 0;
		rawTime->tm_min = 0;
		rawTime->tm_sec = 0;
	}
	else {
		sscanf(t.c_str(), "%d.%d.%d. %d:%d:%d", &day, &month, &year, &hour, &minute, &second);
		rawTime->tm_year = year - 1900;
		rawTime->tm_mon = month - 1;
		rawTime->tm_mday = day;
		rawTime->tm_hour = hour;
		rawTime->tm_min = minute;
		rawTime->tm_sec = second;
	}
	return mktime(rawTime);
}

void SetTimeStamp::run(chars& params, string param1, string param2) {
	time_t setTime = getTime(param2);
	for (auto& file : recursive_directory_iterator(current_path())) {
		string fileToAdd;
		if (params.size()>0 && params[0] == 'p') {
			fileToAdd = absolute(file.path()).string();
		}
		else if (params.size() == 0 || params[0] == 'f') {
			fileToAdd = file.path().filename().string();
		}
		else throw NonExistingOption();
		//try{
			if (match(const_cast<char*>(param1.c_str()), const_cast<char*>(fileToAdd.c_str())))
				std::experimental::filesystem::last_write_time(file, std::chrono::system_clock::from_time_t(setTime));
		//}
		//catch (exception& exc) {}
	}

}