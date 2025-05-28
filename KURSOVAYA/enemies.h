#ifndef ENEMIES_H
#define ENEMIES_H

#include <string>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "services.h"

enum class ConsoleSide {
	left, l,
	right, r,
	bottom, b,
	random, rnd,
};

enum class EnemySide {
	left, l,
	right, r,
};

struct Enemy {
private:
	int old_enemy_upper_left_x;
	int old_enemy_upper_left_y;

public:
	int difficult = 3;
	int enemy_upper_left_x;
	int enemy_upper_left_y;
	EnemySide position;
	int level = 1;


	static const std::string pos_right[4];
	static const std::string pos_left[4];

	static size_t enemies_array_size;
	static Enemy* enemies;

	static void init_enemy_in_array(const ConsoleSide console_side, const int level, const Player& player);
	static void rebuild_array_without_element(const size_t index);
	static void check_merge_all();
	static void delete_array();


	Enemy() {};
	Enemy(const ConsoleSide console_side, const int level, const Player player) : level(level* difficult), old_enemy_upper_left_x(-1), old_enemy_upper_left_y(-1) {
		// Спавним по правой левой или нижней стороне
		if (console_side == ConsoleSide::right || console_side == ConsoleSide::r) { // правая сторона
			enemy_upper_left_x = get_console_width() - pos_right[0].size();
			enemy_upper_left_y = rand() % (get_console_height() - sizeof(pos_right) / sizeof(pos_right[0]));
		}
		else if (console_side == ConsoleSide::left || console_side == ConsoleSide::l) { // левая сторона
			enemy_upper_left_x = 2;
			enemy_upper_left_y = rand() % (get_console_height() - sizeof(pos_right) / sizeof(pos_right[0]));
		}
		else if (console_side == ConsoleSide::bottom || console_side == ConsoleSide::b) { // низ
			enemy_upper_left_x = rand() % (get_console_width() - pos_right[0].size());
			enemy_upper_left_y = get_console_height() - sizeof(pos_right) / sizeof(pos_right[0]);
		}
		else  if (console_side == ConsoleSide::random || console_side == ConsoleSide::rnd) { // рандом
			int random_side = rand() % 3;
			if (random_side == 0) { // Справа
				enemy_upper_left_x = get_console_width() - pos_right[0].size();
				enemy_upper_left_y = rand() % (get_console_height() - sizeof(pos_right) / sizeof(pos_right[0]));
			}
			else if (random_side == 1) { // Слева
				enemy_upper_left_x = 2;
				enemy_upper_left_y = rand() % (get_console_height() - sizeof(pos_right) / sizeof(pos_right[0]));
			}
			else { // Снизу
				enemy_upper_left_x = rand() % (get_console_width() - pos_right[0].size());
				enemy_upper_left_y = get_console_height() - sizeof(pos_right) / sizeof(pos_right[0]);
			}
		}
		// Спавнится сразу повернутым в нужную сторону 
		if (enemy_upper_left_x > player.player_x) {
			position = EnemySide::r;
		}
		else {
			position = EnemySide::l;
		}
	}

	void move(const Player& player, int points_x, int points_y);
	void set_enemy_color() const;
	void print_all() const;
	void save_old_cords();
	void clear_enemy() const;
	void merge(const int other_level);
	bool is_enemy_on_player(const Player& player) const;
};

#endif
