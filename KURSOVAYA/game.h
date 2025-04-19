#pragma once
#include <string>
#include "player.h"

enum Mode {
	FirstTime,
	Castle,
	Battle,
};

struct Game {
	Player player;
	bool run = true;
	bool is_player_die = false;
	bool can_update_level = false;
	bool can_change_location = true;
	bool is_level_passed = false;
	int player_attack_timer = 0;
	int wave = 1;
	int killer_id;
	unsigned long long counter = 0;

	Mode mode;

	static void start();
	void update_data();
	void init_loop();

	~Game();
	
private:
	void process_first_time();
	void process_castle();
	void process_battle();

	bool check_exit_requested();
	bool handle_resize() const;

	void process_enemies();
	void handle_player_death();
	void process_player(Player& player, const Color color = Green) const;

	void init_first_start();
	void init_from_saved_state();
};