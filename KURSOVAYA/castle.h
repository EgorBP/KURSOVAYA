#ifndef CASTLE_H
#define CASTLE_H

#include <string>
#include "player.h"

struct Castle {
	static const int free_left_space = 45;   // x pos
	static const int empty_spaces = 8;       // y pos
	static const int door_y_pos = empty_spaces + 17;
	static const std::string castle[];

	static void print_castle(const Player& player);
	static int find_door_index();
};

#endif
