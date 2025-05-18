#include <iostream>
#include "services.h"
#include "player.h"
#include "enemies.h"

using namespace std;


size_t Enemy::enemies_array_size = 0;
Enemy* Enemy::enemies = nullptr;

const string Enemy::pos_right[4] = {
		"`oo.'    ",
		"`-')  ,. ",
		" ( `-'/^`",
		" -`_-)   "
};
const string Enemy::pos_left[4] = {
		"    `.oo'",
		" ,.  (`-'",
		"'^\\`-' ) ",
		"   c-L'- ",
};

void Enemy::init_enemy_in_array(const console_side console_side, const int level, const Player& player) {
	// ����������� ������ ������
	Enemy* new_array = new Enemy[enemies_array_size + 1];

	for (size_t i = 0; i < enemies_array_size; i++) { // �������� ������ ������
		new_array[i] = enemies[i];
	}

	new_array[enemies_array_size] = Enemy(console_side, level, player);

	delete[] enemies;
	enemies = new_array;
	enemies_array_size++;
}

void Enemy::rebuild_array_without_element(const size_t index) {
	if (!enemies) return;

	Enemy* new_array = new Enemy[enemies_array_size - 1];
	for (size_t i = 0, j = 0; i < enemies_array_size; i++) {
		if (i != index) {
			new_array[j] = enemies[i];
			j++;
		}
	}

	delete[] enemies;
	enemies = new_array;
	enemies_array_size--;
}

void Enemy::check_merge_all() {
	for (int i = 0; i < enemies_array_size; i++) {
		int x_main = enemies[i].old_enemy_upper_left_x;
		int y_main = enemies[i].old_enemy_upper_left_y;

		for (int i_checker = 0; i_checker < enemies_array_size; i_checker++) {
			if (i != i_checker) {
				int x_other = enemies[i_checker].enemy_upper_left_x;
				int y_other = enemies[i_checker].enemy_upper_left_y;

				if (abs(x_main - x_other) < 9 && abs(y_main - y_other) < 3) {
					enemies[i_checker].merge(enemies[i].level); // �������� �������
					enemies[i].clear_enemy();                   // ������� ����� ���������
					enemies[i_checker].clear_enemy();           // ������� � ������ ������ � ���� �� �������� ����� �������
					enemies[i_checker].print_all();             //  ����� ������������� (��������) � �������� �������� �� ����������
					rebuild_array_without_element(i);           // �������
					i--;										// ���������� i �� ��� �� ������� ��� ��� �� ��� ����� ������ ����� ������� ������� ����� ���������
					break;
				}
			}
		}
	}
}

void Enemy::delete_array() {
	delete[] enemies;
	enemies = nullptr;
	enemies_array_size = 0;
}


void Enemy::move(const Player& player, int point_x, int point_y) {
	// �������� 2 ������ ��������� �������
	if (level > 4 * difficult) {
		point_x += 2;
		point_y++;
	}
	else if (level > 2 * difficult) {
		point_x++;
	}

	// ���������� �� ����� ������������ (������ �������� ����) �� ������
	int distance_x = 4;
	int distance_y = 2;

	// ����� �������� �� ��������� �� ������ ������ �� ��������
	const int player_x = player.player_x;
	const int player_y = player.player_y;
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

	// �����
	int enemy_center_x = enemy_upper_left_x + distance_x;
	int	enemy_center_y = enemy_upper_left_y + distance_y;
	// ���� ����
	int x_difference = player_x - enemy_center_x;
	int y_difference = player_y - enemy_center_y;

	// �������� �� X � ������ ����� (����� �������� �������)
	if (std::abs(x_difference) > 1) {
		if (x_difference > 0) {
			enemy_upper_left_x += point_x;
			position = enemy_side::l;
		}
		else {
			enemy_upper_left_x -= point_x;
			position = enemy_side::r;
		}
	}

	// �������� �� Y
	if (y_difference > 0) {
		enemy_upper_left_y += point_y;
	}
	else if (y_difference < 0) {
		enemy_upper_left_y -= point_y;
	}
}

void Enemy::set_enemy_color() const {
	int color = 7;  // �����
	//if (level == 1) color = color;
	//else if (level == 2) color = 6; // ������
	//else if (level == 3) color = 4; // �������
	//else if (level == 4) color = 5; // ���������
	//else if (level <= 0) color = 7;
	//else color = 5; // ���������

	if (level > 3 * difficult) color = 5; // ���������
	else if (level > 2 * difficult) color = 4; // �������
	else if (level > 1 * difficult) color = 6; // ������
	else color = color; // �����
	set_text_color(color);
}

void Enemy::print_all() const {
	set_enemy_color();
	const string* model;
	if (position == enemy_side::r) model = pos_right;
	else model = pos_left;
	for (int i = 0; i < 4; i++) {
		move_cursor(enemy_upper_left_x, enemy_upper_left_y + i);
		cout << model[i];
	}
	set_text_color(7);
}

void Enemy::save_old_cords() {
	old_enemy_upper_left_x = enemy_upper_left_x;
	old_enemy_upper_left_y = enemy_upper_left_y;
}

void Enemy::clear_enemy() const {
	if (old_enemy_upper_left_x == -1 || old_enemy_upper_left_y == -1) {
		return;
	}

	const int console_width = get_console_width();
	const int console_height = get_console_height();

	for (int i = 0; i < 4; i++) {
		int pos_x = old_enemy_upper_left_x;
		int pos_y = old_enemy_upper_left_y + i;

		if (pos_x < 0) pos_x = 0;
		if (pos_y < 0 || pos_y >= console_height) continue;

		int width = min(9, console_width - pos_x);
		clear(pos_x, pos_y, width);
	}
}

void Enemy::merge(const int other_level) {
	level += other_level;
}

bool Enemy::is_enemy_on_player(const Player& player) const {
	// ������� true ���� � ����� ����� false
	const int player_x = player.player_x;
	const int player_y = player.player_y;

	if ((player_x >= enemy_upper_left_x && player_x <= enemy_upper_left_x + 8) &&
		player_y >= enemy_upper_left_y && player_y <= enemy_upper_left_y + 3) {
		return true;
	}
	return false;
}

