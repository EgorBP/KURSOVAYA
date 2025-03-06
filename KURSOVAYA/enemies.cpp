#include "enemies.h"
#include <iostream>
#include "services.h"

using namespace std;


void Enemy::print() const {
	const string* model;
	if (position == 'r') model = pos_rigth;
	else model = pos_left;
	for (int i = 0; i < 4; i++) {
		move_cursor(enemy_upper_left_x, enemy_upper_left_y + i);
		cout << model[i];
	}
}

void Enemy::clear_enemy() const {
	for (int i = 0; i < 6; i++) {
		//move_cursor(enemy_upper_left_x, enemy_upper_left_y + i);
		clear(enemy_upper_left_x - 1, enemy_upper_left_y - 1 + i, 11);
	}

}

void Enemy::move(int player_x, int player_y) {
	int enemy_center_x = enemy_upper_left_x + 5, enemy_center_y = enemy_upper_left_y + 2;
	int x_difference = player_x - enemy_center_x, y_difference = player_y - enemy_center_y;

	if (x_difference > 0) {
		position = 'l';
	}
	else position = 'r';

	if (x_difference != 0) {
		enemy_upper_left_x += (x_difference > 0) ? 1 : -1;
	}

	if (y_difference != 0) {
		enemy_upper_left_y += (y_difference > 0) ? 1 : -1;
	}
}


