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
};

void Enemy::move(int player_x, int player_y) {

}


