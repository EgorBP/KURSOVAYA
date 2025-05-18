#pragma once
#include <chrono>


struct Bomb {
	static void process_bomb();
	static void boom();
	static bool check_boom();
	static void print_count();
	static int get_current_count();
	static void count_up(const int points = 1);
	static void set_new_count(const int new_level);

	static const std::string filename;

private:
	static std::chrono::steady_clock::time_point last_boom_time;
	static const int boom_timer = 500;
};
