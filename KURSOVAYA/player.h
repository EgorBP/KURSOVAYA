#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player {
	int player_x;
	int player_y;
	char player_side;
	int old_player_x;
	int old_player_y;

	Player() : player_x(77), player_y(25), player_side('^') {}
	Player(const int x, const int y) : player_x(x), player_y(y), player_side('^') {}

	void player_clear() const;
	void player_print(const std::string& color = "green") const;
	void player_move(const int points_x = 2, const int points_y = 1);
	bool is_player_on_door(const int door_x, const int door_y, const int door_width) const;
};

#endif
