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

	Enemy(int x, int y) : enemy_upper_left_x(x), enemy_upper_left_y(y) {}

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
	void save_old_cords();
	void clear_enemy() const;
	static void check_merge_all(Enemy** enemies, const int size);
	void merge(const int other_level);
	bool is_enemy_on_player(const Player& player) const;
	void move(Player& player, const int point_x, const int point_y);
};

#endif
