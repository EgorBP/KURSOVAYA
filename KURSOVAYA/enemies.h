#ifndef ENEMIES_H
#define ENEMIES_H

#include <iostream>
#include "player.h"

struct Enemy {
	short enemy_upper_left_x;
	short enemy_upper_left_y;
	short old_enemy_upper_left_x;
	short old_enemy_upper_left_y;
	char position = 'r';
	short level = 1;

	const std::string pos_rigth[4] = {
		"`oo.'    ",
		"`-')  ,. ",
		" ( `-'/^`",
		" -`_-)   "
	};
	const std::string pos_left[4] = {
		"    `.oo'",
		" ,.  (`-'",
		"'^\\`-' ) ",
		"   c-L'- ",
	};

	void set_enemy_color() const;
	void print() const;
	void clear_enemy();
	static void check_merge_all(Enemy** enemies, int size);
	void merge(int other_level);
	bool is_enemy_on_player(Player& player) const;
	void move(Player& player, int ponts_x, int point_y, short distance_x = 4, short distance_y = 2);
};

#endif
