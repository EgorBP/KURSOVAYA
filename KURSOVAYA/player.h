#ifndef PLAYER_H
#define PLAYER_H

struct Player {
	int player_x;
	int player_y;
	char player_side;

	Player() : player_x(77), player_y(25), player_side('^') {}
	Player(int x, int y) : player_x(x), player_y(y), player_side('^') {}

	void player_print() const;
	void player_move();
};

#endif
