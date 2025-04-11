#ifndef BOW_H
#define BOW_H

#include "enemies.h"

struct Arrow {
	int arrow_x;
	int arrow_y;
	char arrow_side;

	static size_t arrows_array_size;
	static Arrow* arrows;

	static void init_new_arrow(Player& player);
	static void rebuild_array_without_element(const size_t index);
	static void process_arrows();
	static void print_arrow_array_size();
	static void delete_array();

	void arrow_clear() const;
	bool is_arrow_border() const;
	void print_arrow() const;
	bool is_arrow_on_enemy(const int enemy_x, const int enemy_y) const;

	Arrow() {};
	Arrow(const Player& player) : arrow_x(player.player_x), arrow_y(player.player_y), arrow_side(player.player_side) {};
};

#endif
