﻿#include <iostream>
#include <Windows.h>
#include <fstream>
#include "services.h"
#include "enemies.h"
#include "level.h"

using namespace std;

const int Level::max_level = 10;

int Level::get_current_level() {
	int level = 0;
	fstream file("level.txt", ios::in);
	if (file.is_open()) {
		file >> level;
		file.close();
	}
	else {
		set_new_level(level);
	}
	return level;
}

void Level::level_up(const int points) {
	int current_level = get_current_level();
	fstream file("level.txt", ios::out | ios::trunc);
	if (file.is_open()) {
		file << current_level + points;
		file.close();
	}
}

void Level::set_new_level(const int new_level) {
	fstream file("level.txt", ios::out);
	if (file.is_open()) {
		file << new_level;
		file.close();
	}
}

void Level::print_level(bool is_passed) {
	if (is_passed) {
		set_text_color("green");
	}
	else {
		set_text_color("red");
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

void Level::print_timer(const int timer) {
	move_cursor(0, 6);

	if (timer <= -1) {
		set_text_color("green");
		cout << 0;
		set_color();
	}
	else {
		if (timer == 99) {
			clear(0, 6, 2);
			move_cursor(0, 6);
		}
		cout << timer / 10;
	}
	move_cursor();
}


void Level::init_level(const int wave, const Player& player, int& timer) {
	void (*levels[max_level + 1])(const int wave, const Player & player, int& timer) = {
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
	levels[get_current_level()](wave, player, timer);
}

void Level::init_0_level(const int wave, const Player& player, int& timer) {
	// Присвоить -1 после всех волн
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("right", 1, player);
		timer = -1;
		return;
	default:
		timer = -1;
	}
	timer = 150;
}

void Level::init_1_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("left", 1, player);
		break;
	case 2:
		Enemy::init_enemy_in_array("left", 1, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 100;
}

void Level::init_2_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("right", 1, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		timer = 100;
		return;
	case 2:
		Enemy::init_enemy_in_array("bottom", 2, player);
		Enemy::init_enemy_in_array("bottom", 2, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 150;
}

void Level::init_3_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("bottom", 1, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		timer = 100;
		return;
	case 2:
		Enemy::init_enemy_in_array("bottom", 1, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 150;
}

void Level::init_4_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("l", 1, player);
		timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array("r", 1, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		Enemy::init_enemy_in_array("r", 1, player);
		break;
	case 3:
		Enemy::init_enemy_in_array("r", 1, player);
		Enemy::init_enemy_in_array("bottom", 2, player);
		Enemy::init_enemy_in_array("bottom", 1, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 200;
}

void Level::init_5_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("r", 1, player);
		Enemy::init_enemy_in_array("l", 1, player);
		Enemy::init_enemy_in_array("b", 1, player);
		timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("l", 3, player);
		Enemy::init_enemy_in_array("b", 2, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 200;

}

void Level::init_6_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("r", 1, player);
		Enemy::init_enemy_in_array("r", 1, player);
		Enemy::init_enemy_in_array("r", 1, player);
		timer = 120;
		return;
	case 2:
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array("b", 3, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("b", 3, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 220;
}

void Level::init_7_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("l", 1, player);
		Enemy::init_enemy_in_array("r", 2, player);
		timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("r", 1, player);
		break;
	case 3:
		Enemy::init_enemy_in_array("l", 3, player);
		Enemy::init_enemy_in_array("b", 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array("b", 3, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 200;
}

void Level::init_8_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		timer = 150;
		return;
	case 2:
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array("l", 3, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array("b", 3, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("b", 3, player);
		Enemy::init_enemy_in_array("b", 2, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 200;
}

void Level::init_9_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("l", 1, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("r", 1, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("b", 1, player);
		Enemy::init_enemy_in_array("r", 2, player);
		break;
	case 2:
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("l", 1, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		break;
	case 3:
		Enemy::init_enemy_in_array("l", 3, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array("b", 3, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("b", 3, player);
		Enemy::init_enemy_in_array("r", 2, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 250;
}

void Level::init_10_level(const int wave, const Player& player, int& timer) {
	switch (wave) {
	case 1:
		Enemy::init_enemy_in_array("l", 1, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array(" ", 1, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("b", 1, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array(" ", 1, player);
		break;
	case 2:
		Enemy::init_enemy_in_array(" ", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("b", 2, player);
		Enemy::init_enemy_in_array(" ", 2, player);
		Enemy::init_enemy_in_array("r", 1, player);
		break;
	case 3:
		Enemy::init_enemy_in_array(" ", 3, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array(" ", 3, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array(" ", 2, player);
		break;
	case 4:
		Enemy::init_enemy_in_array(" ", 3, player);
		Enemy::init_enemy_in_array(" ", 2, player);
		Enemy::init_enemy_in_array("b", 3, player);
		Enemy::init_enemy_in_array(" ", 2, player);
		Enemy::init_enemy_in_array(" ", 1, player);
	case 5:
		Enemy::init_enemy_in_array("b", 4, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("r", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		Enemy::init_enemy_in_array("l", 2, player);
		timer = -1;
		return;
	default:
		timer = -1;
		return;
	}
	timer = 250;
}
