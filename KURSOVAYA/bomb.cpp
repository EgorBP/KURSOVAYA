#include <iostream>
#include <fstream>
#include "services.h"
#include "enemies.h"
#include "bomb.h"

using namespace std;

void Bomb::boom() {
	if (get_current_count() > 0) {
		count_up(-1);

		if (!Enemy::enemies) return;

		for (size_t i{ 0 }; i < Enemy::enemies_array_size; i++) {
			Enemy::enemies[i].merge(-5);
		}
	}
}

int Bomb::get_current_count() {
	int level = 0;
	fstream file("bomb.txt", ios::in);
	if (file.is_open()) {
		file >> level;
		file.close();
	}
	else {
		set_new_count(level);
	}
	return level;
}

void Bomb::count_up(const int points) {
	int current_level = get_current_count();
	fstream file("bomb.txt", ios::out | ios::trunc);
	if (file.is_open()) {
		file << current_level + points;
		file.close();
	}
}

void Bomb::set_new_count(const int new_level) {
	fstream file("bomb.txt", ios::out | ios::trunc);
	if (file.is_open()) {
		file << new_level;
		file.close();
	}
}