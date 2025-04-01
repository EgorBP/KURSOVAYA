#ifndef BOW_H
#define BOW_H

#include "enemies.h"

struct Arrow {
	int arrow_x;
	int arrow_y;
	char arrow_side;

	Arrow(int x, int y, char side) : arrow_x(x), arrow_y(y), arrow_side(side) {}

	void arrow_clear() const;
	bool is_arrow_border() const;
	void print_arrow() const;
	bool is_arrow_on_enemy(const int enemy_x, const int enemy_y) const;
	static void arrow_move(Arrow** arrows, Enemy** enemies, const int bullets, const int size);
};

#endif
