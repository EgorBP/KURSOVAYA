#include <iostream>
#include <Windows.h>
#include <fstream>
#include "services.h"
#include "enemies.h"
#include "level.h"

using namespace std;

int Level::wave_timer = 0;

const string Level::filename = "Data\\level.txt";

int Level::get_current_level() {
	int level = 0;
	fstream file(Level::filename, ios::in);
	if (file.is_open()) {
		file >> level;
		file.close();
	}
	else {
		set_new_level(level);
	}
	file.close();
	return level;
}

void Level::level_up(const int points) {
	int current_level = get_current_level();
	fstream file(Level::filename, ios::out | ios::trunc);
	if (file.is_open()) {
		file << current_level + points;
		file.close();
	}
}

void Level::set_new_level(const int new_level) {
	fstream file(Level::filename, ios::out | ios::trunc);
	if (file.is_open()) {
		file << new_level;
		file.close();
	}
}

void Level::print_level(bool is_passed) {
	if (is_passed) {
		set_text_color(Color::Green);
	}
	else {
		set_text_color(Color::Red);
	}

	move_cursor(0, 0);
	if (get_current_level() < 0) {
		cout << 0;
	}
	else {
		cout << get_current_level();
	}

	move_cursor(0, 1);
	if ((max_level + 1) % 10 > 0) {
		cout << "--";
	}
	else cout << '-';

	move_cursor(0, 2);
	cout << max_level;

	move_cursor();
	set_color();
}

void Level::print_timer() {
	move_cursor(0, 6);

	if (wave_timer <= -1) {
		set_text_color(Color::Green);
		cout << 0;
		set_color();
	}
	else {
		if (wave_timer == 99) {
			clear(0, 6, 2);
			move_cursor(0, 6);
		}
		cout << wave_timer / 10;
	}
	move_cursor();
}


void Level::init_level(const int wave, const Player& player) {
	void (*levels[max_level + 1])(const int wave, const Player & player) = {
		init_0_level,
		init_1_level,
		init_2_level,
		init_3_level,
		init_4_level,
		init_5_level,
		init_6_level,
		init_7_level,
		init_8_level,
		init_9_level,
		init_10_level,
	};
	levels[get_current_level()](wave, player);
}

void Level::init_0_level(const int wave, const Player& player) {
	// Присвоить -1 после всех волн
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::right, 1, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
	}
	wave_timer = 150;
}

void Level::init_1_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::left, 1, player);
		break;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::left, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 100;
}

void Level::init_2_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::right, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		wave_timer = 100;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 2, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 150;
}

void Level::init_3_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		wave_timer = 100;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 150;
}

void Level::init_4_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		wave_timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 200;
}

void Level::init_5_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 1, player);
		wave_timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 200;
}

void Level::init_6_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		wave_timer = 120;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::b, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 3, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 220;
}

void Level::init_7_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		wave_timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::l, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array(ConsoleSide::b, 3, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 200;
}

void Level::init_8_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		wave_timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::l, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array(ConsoleSide::b, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 200;
}

void Level::init_9_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		break;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::r, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::b, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::l, 3, player);
		break;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 300;
}

void Level::init_10_level(const int wave, const Player& player) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array(ConsoleSide::left, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::left, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 1, player);
		Enemy::init_enemy_in_array(ConsoleSide::right, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 1, player);
		break;
	case 2:
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::right, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::left, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::right, 1, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::right, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::left, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 3, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::rnd, 1, player);
		break;
	case 5:
		Enemy::init_enemy_in_array(ConsoleSide::bottom, 4, player);
		Enemy::init_enemy_in_array(ConsoleSide::right, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::right, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::left, 2, player);
		Enemy::init_enemy_in_array(ConsoleSide::left, 2, player);
		wave_timer = -1;
		return;
	default:
		wave_timer = -1;
		return;
	}
	wave_timer = 250;
}

