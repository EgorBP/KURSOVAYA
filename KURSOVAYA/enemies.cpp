#include "enemies.h"
#include <iostream>
#include "services.h"

using namespace std;

void Enemy::set_enemy_color() const {
	int color = 7;  // Белый
	if (level == 1) color = color;
	else if (level == 2) color = 6; // Желтый
	else if (level == 3) color = 4; // Красный
	else if (level == 4) color = 5; // Пурпурный
	else color = 5; // Пурпурный
	set_color(color);
}

void Enemy::print() const {
	set_enemy_color();
	const string* model;
	if (position == 'r') model = pos_rigth;
	else model = pos_left;
	for (int i = 0; i < 4; i++) {
		move_cursor(enemy_upper_left_x, enemy_upper_left_y + i);
		cout << model[i];
	}
	set_color(7);
}

void Enemy::clear_enemy() {
	int console_width = 156;
	int console_height = 46;

	for (int i = 0; i < 4; i++) {
		int pos_x = old_enemy_upper_left_x;
		int pos_y = old_enemy_upper_left_y + i;

		if (pos_x < 0) pos_x = 0;
		if (pos_y < 0 || pos_y >= console_height) continue;

		int width = min(9, console_width - pos_x);
		clear(pos_x, pos_y, width);
	}
	old_enemy_upper_left_x = enemy_upper_left_x;
	old_enemy_upper_left_y = enemy_upper_left_y;
}

void Enemy::merge(int other_level) {
	level += other_level;
}

void Enemy::move(int player_x, int player_y, int point_x, int point_y, short distance_x, short distance_y) {
	// Чтобы динозавр не переходил на другие строки на границах
	if (player_x <= 4) {
		distance_x -= 4;
	}
	else if (player_x >= 152) {
		distance_x += 4;
	}
	if (player_y <= 2) {
		distance_y -= 2;
	}
	else if (player_y >= 45) {
		distance_y += 1;
	}

	// Куда идти
	int enemy_center_x = enemy_upper_left_x + distance_x, enemy_center_y = enemy_upper_left_y + distance_y;
	int x_difference = player_x - enemy_center_x, y_difference = player_y - enemy_center_y;

	if (x_difference > 0) {
		enemy_upper_left_x += point_x;
	}
	else if (x_difference < 0) {
		enemy_upper_left_x -= point_x;
	}
	if (y_difference > 0) {
		enemy_upper_left_y += point_y;
	}
	else if (y_difference < 0) {
		enemy_upper_left_y -= point_y;
	}

	// Сторона (если равно сохраняем сторону куда он шел до этого)
	if (x_difference > 0) {
		position = 'l';
	}
	else if (x_difference < 0) {
		position = 'r';
	}
}


