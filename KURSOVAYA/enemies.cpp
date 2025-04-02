#include "enemies.h"
#include <iostream>
#include "services.h"
#include "player.h"

using namespace std;

void Enemy::set_enemy_color() const {
	int color = 7;  // Белый
	if (level == 1) color = color;
	else if (level == 2) color = 6; // Желтый
	else if (level == 3) color = 4; // Красный
	else if (level == 4) color = 5; // Пурпурный
	else if (level <= 0) color = 7;
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

void Enemy::check_merge_all(Enemy** enemies, int size) {
	for (int i = 0; i < size; i++) {
		if (enemies[i]) {
			int x_main = enemies[i]->enemy_upper_left_x;
			int y_main = enemies[i]->old_enemy_upper_left_y;

			for (int i_checker = 0; i_checker < size; i_checker++) {
				if (enemies[i_checker] && i != i_checker) {

					int x_other = enemies[i_checker]->enemy_upper_left_x;
					int y_other = enemies[i_checker]->enemy_upper_left_y;

					if (abs(x_main - x_other) < 9 && abs(y_main - y_other) < 3) {
						enemies[i_checker]->merge(enemies[i]->level); // Повышаем уровень
						enemies[i]->clear_enemy();                    // Очищаем перед удалением
						enemies[i_checker]->clear_enemy();            // Очищаем и рисуем заново в этой же итерации чтобы создать
						enemies[i_checker]->print();                  //  эффкт переваривания (задержка) и перебить очищение от удаленного
						enemies[i] = nullptr;                         // Удаляем
					}
				}
			}
		}
	}
}

void Enemy::merge(int other_level) {
	level += other_level;
}

bool Enemy::is_enemy_on_player(Player& player) const {
	// Вернуть true враг в герое иначе false
	int player_x = player.player_x;
	int player_y = player.player_y;

	if ((player_x >= enemy_upper_left_x && player_x <= enemy_upper_left_x + 8) &&
		player_y >= enemy_upper_left_y && player_y <= enemy_upper_left_y + 3) {
		return true;
	}
	return false;
}

void Enemy::move(Player& player, int point_x, int point_y, short distance_x, short distance_y) {
	// Чтобы динозавр не переходил на другие строки на границах
	int player_x = player.player_x;
	int player_y = player.player_y;
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
