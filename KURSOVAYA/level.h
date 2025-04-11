#pragma once
#include "enemies.h"

struct Level {
	static const int max_level;

	static int get_current_level();
	static void level_up(const int points = 1);
	static void set_new_level(const int new_level);
	static void print_level();
	static void print_timer(const int timer);
	static void init_level(const int wave, const Player& player, int& timer);

private:
	static void init_0_level(const int wave, const Player& player, int& timer);
	static void init_1_level(const int wave, const Player& player, int& timer);
	static void init_2_level(const int wave, const Player& player, int& timer);
	static void init_3_level(const int wave, const Player& player, int& timer);
	static void init_4_level(const int wave, const Player& player, int& timer);
	static void init_5_level(const int wave, const Player& player, int& timer);
	static void init_6_level(const int wave, const Player& player, int& timer);
	static void init_7_level(const int wave, const Player& player, int& timer);
	static void init_8_level(const int wave, const Player& player, int& timer);
	static void init_9_level(const int wave, const Player& player, int& timer);
	static void init_10_level(const int wave, const Player& player, int& timer);
};
