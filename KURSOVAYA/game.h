#pragma once
#include <string>
#include "player.h"

struct Game {
	bool flag_end_game = false;
	bool can_update_level = false;
	bool can_change_location = true;
	bool is_level_passed = false;
	int player_attack_timer = 0;
	int intit_wave_timer = 0;
	int wave = 1;
	int killer_id;
	unsigned long long counter = 0;

	std::string mode;
	Player player;

	static void start();
	void update_data();
	void init_loop();
};