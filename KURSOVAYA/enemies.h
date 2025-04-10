#ifndef ENEMIES_H
#define ENEMIES_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "services.h"

struct Enemy {
	int difficult = 3;
	int enemy_upper_left_x;
	int enemy_upper_left_y;
	int old_enemy_upper_left_x;
	int old_enemy_upper_left_y;
	char position;
	int level = 1;

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

	Enemy(const std::string& console_side, const int level, const Player player) : level(level * difficult) {
		// Спавним по правой левой или нижней стороне
		srand(time(0));
		if (console_side == "right") { // правая сторона
			enemy_upper_left_x = get_console_width() - pos_rigth[0].size();
			enemy_upper_left_y = rand() % (get_console_height() - sizeof(pos_rigth) / sizeof(pos_rigth[0]));
		}
		else if (console_side == "left") { // левая сторона
			enemy_upper_left_x = 2;
			enemy_upper_left_y = rand() % (get_console_height() - sizeof(pos_rigth) / sizeof(pos_rigth[0]));
		}
		else { // низ
			enemy_upper_left_x = rand() % (get_console_width() - pos_rigth[0].size());
			enemy_upper_left_y = get_console_height() - sizeof(pos_rigth) / sizeof(pos_rigth[0]);
		}
		// Спавнится сразу повернутым в нужную сторону 
		if (enemy_upper_left_x > player.player_x) {
			position = 'r';
		}
		else {
			position = 'l';
		}
	}

	void set_enemy_color() const;
	void print() const;
	void save_old_cords();
	void clear_enemy() const;
	static void init_enemy_in_array(const std::string& console_side, const int level, const Player& player, Enemy** enemies);
	static void check_merge_all(Enemy** enemies, const int size);
	void merge(const int other_level);
	bool is_enemy_on_player(const Player& player) const;
	void move(const Player& player, int points_x, int points_y);
	static void delete_array(Enemy** arrows, const int size);
};

#endif
