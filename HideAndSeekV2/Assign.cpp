#include "Assign.h"

void Assign::run(chars params, string param1, string param2) {
	if (params.size() == 0 || params[0] == 'f') {
		Aliases::fetchAliases()->addAlias(param1, new File(param2));
		cout << "Added alias : " << param1 << endl;
		return;
	}
	else if (params.size()>0 && params[0] == 's') {
		Simbolics::fetchSimbolics()->addSimb(param1, Selections::findSelection(param2));
		cout << "Added simbolic name : " << param1 << endl;
		return;
	}
	else throw new NonExistingOption();
}