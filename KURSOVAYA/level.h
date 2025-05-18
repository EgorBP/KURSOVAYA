#pragma once
#include "enemies.h"

struct Level {
	static const int max_level = 10;
	static int wave_timer;

	static const std::string filename;

	static int get_current_level();
	static void level_up(const int points = 1);
	static void set_new_level(const int new_level);
	static void print_level(bool is_passed = true);
	static void print_timer();
	static void init_level(const int wave, const Player& player);
	
// При добавлении нового уровня:
//  1. Увеличить max_level на 1
//	2. Добавить функцию здесь
//  3. Добавить указатель в массив в init_level
private:
	static void init_0_level(const int wave, const Player& player);
	static void init_1_level(const int wave, const Player& player);
	static void init_2_level(const int wave, const Player& player);
	static void init_3_level(const int wave, const Player& player);
	static void init_4_level(const int wave, const Player& player);
	static void init_5_level(const int wave, const Player& player);
	static void init_6_level(const int wave, const Player& player);
	static void init_7_level(const int wave, const Player& player);
	static void init_8_level(const int wave, const Player& player);
	static void init_9_level(const int wave, const Player& player);
	static void init_10_level(const int wave, const Player& player);
};
