#include "Aliases.h"

Aliases* Aliases::AliasesMap = new Aliases();

void Aliases::addAlias(string alias, File* object){
	if (object) map.insert({ alias, object }); 
}

File* Aliases::findObject(string al){
	if (map.count(al) == 0) return nullptr;
	return map.at(al);
}

void Aliases::loadAlias(path pathh) {
	fstream file;
	file.open(pathh.string().c_str(), std::fstream::in);
	int word = 1;
	string readWord, aliasName, fileName;
	while (file >> readWord) {
		if (word == 1) {
			aliasName = readWord;
			word = 2;
		}
		else {
			fileName = readWord;
			word = 1;
			if(exists(fileName)) map.insert({ aliasName, new File(fileName) });
		}
	}
	file.close();
}

void Aliases::saveAlias(path pathh) {
	fstream file;
	chars params(0);
	(new MakeFile())->run(params, pathh.string(), "");
	file.open(pathh.string().c_str(), std::fstream::out);
	for (auto& alias : map) {
		file << alias.first << " " << alias.second->filePath() << "\n";
	}
	file.close();
}