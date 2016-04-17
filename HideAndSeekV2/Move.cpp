#include "Move.h"

Move* Move::move = new Move();
int movee = 0;

void Move::run(chars params, string param1, string param2) {
	movee = 1;
	params.resize(1);
	params[0] = 'r';
	param2.append("/"); string fname = param1.substr(param1.find_last_of("/") + 1);
	param2.append(fname);
	Copy::fetch()->run(params, param1, param2);
	params[0] = 'a';
	Delete::fetch()->run(params, param1, param2);
	movee = 0;
}