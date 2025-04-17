#include <iostream>
#include "services.h"
#include "game.h"

int main() {
	prepare_console();

	Game::start();

	return 0;
}