#ifndef ENEMIES_H
#define ENEMIES_H

#include <iostream>

struct Enemy {
	short enemy_upper_left_x;
	short enemy_upper_left_y;
	char position = 'r';
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
	void print() const;
	void clear_enemy() const;
	void move(int player_x, int player_y);
};

#endif
