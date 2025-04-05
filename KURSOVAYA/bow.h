#ifndef BOW_H
#define BOW_H

#include "enemies.h"

struct Arrow {
	int arrow_x;
	int arrow_y;
	char arrow_side;

	Arrow(Player& player) : arrow_x(player.player_x), arrow_y(player.player_y), arrow_side(player.player_side) {}

	static void init_arrow_in_array(Arrow** arrows, Player& player, const int size);
	void arrow_clear() const;
	bool is_arrow_border() const;
	void print_arrow() const;
	bool is_arrow_on_enemy(const int enemy_x, const int enemy_y) const;
	static void arrow_move(Arrow** arrows, Enemy** enemies, const int bullets, const int size);
};

#endif
