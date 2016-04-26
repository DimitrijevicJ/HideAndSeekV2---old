#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <filesystem>
#include <experimental/filesystem>
#include <bitset>
#include <vector>
#include <unordered_map>

#include "Compare.h"
#include "Info.h"
#include "SetTimeStamp.h"
#include "ColorMe.h"
#include "Aliases.h"
#include "Assign.h"
#include "ChangeDirectory.h"
#include "Command.h"
#include "Copy.h"
#include "Exceptions.h"
#include "Help.h"
#include "MakeDirectory.h"
#include "MakeFile.h"
#include "Delete.h"
#include "Move.h"
#include "PrintDirectoryContents.h"
#include "SelectionsNSimbolics.h"
#include "StartNFinish.h"
#include "File.h"
#include "Quit.h"

using namespace std;
using namespace std::experimental::filesystem;

typedef vector<char> chars;

class Selection;

class SelectNode {
public:
	friend class Select;
	SelectNode* left=nullptr, *right=nullptr;
	SelectNode* parent = nullptr;
	SelectNode(SelectNode* par):parent(par){}
	virtual void foo() {}
	Selection* selectFiles(string selectionName, chars params, SelectNode* node);
};
class SelectNodeOperation : public SelectNode {
	friend class Select;
	friend class SelectNode;
public:
	enum OPERATIONS { AND, OR, NOT, XOR };
private:
	OPERATIONS operation;
public:
	OPERATIONS fetchOp() { return operation; }
	SelectNodeOperation(string op, SelectNode* par) : SelectNode(par) {
		if (op == "AND") operation = AND;
		else if (op == "OR") operation = OR;
		else if (op == "NOT") operation = NOT;
		else if (op == "XOR") operation = XOR;
		else throw OperationNotSupported();
	}
	Selection* calculateAnd(SelectNode*, SelectNode*, string param, chars);
	Selection* calculateOr(SelectNode*, SelectNode*, string param, chars);
	Selection* calculateNot(SelectNode*, string param, chars);
	Selection* calculateXor(SelectNode*, SelectNode*, string param, chars);
};
class SelectNodeCriterium : public SelectNode {
	friend class SelectNode;
	string criterium;
public:
	string fetchCrit() { return criterium; }
	SelectNodeCriterium(string crit, SelectNode* par) :SelectNode(par), criterium(crit) {}
};

class Select : public Command{
	static Select* select;
	Select() = default;
	Select(const Select&) = delete;
	Select& operator=(const Select&) = delete;
protected:
	SelectNode* parseCriterium(string criterium);
public:
	static Select* fetch() { return select; }
	void run(chars& params, string param1, string param2);
	static void cleanUp() { delete select; select = nullptr; }
};
