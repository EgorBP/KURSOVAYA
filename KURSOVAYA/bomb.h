#pragma once


struct Bomb {
	static int count;

	static void boom();
	static int get_current_count();
	static void count_up(const int points = 1);
	static void set_new_count(const int new_level);
};