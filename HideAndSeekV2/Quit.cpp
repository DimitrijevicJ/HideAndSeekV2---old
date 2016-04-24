#include "Quit.h"

Quit* Quit::quit = new Quit();

void Quit::run(chars& params, string param1, string param2) {
	end();
}