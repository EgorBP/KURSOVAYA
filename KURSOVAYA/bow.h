#ifndef BOW_H
#define BOW_H

#include "enemies.h"

struct Arrow {
	static size_t arrows_array_size;
	static Arrow* arrows;
	int arrow_x;
	int arrow_y;
	char arrow_side;

	Arrow() {};
	Arrow(const Player& player) : arrow_x(player.player_x), arrow_y(player.player_y), arrow_side(player.player_side) {}

	static void init_new_arrow(Player& player);
	void arrow_clear() const;
	bool is_arrow_border() const;
	void print_arrow() const;
	bool is_arrow_on_enemy(const int enemy_x, const int enemy_y) const;
	static void process_arrows(Enemy** enemies, const size_t size);
	static void delete_array();
};

#endif
