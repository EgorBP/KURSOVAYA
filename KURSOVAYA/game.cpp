#include <iostream>
#include <windows.h>
#include "services.h"
#include "enemies.h"
#include "player.h"
#include "bow.h"
#include "castle.h"
#include "greeting.h"
#include "level.h"
#include "dialogue.h"
#include "bomb.h"
#include "end.h"
#include "game.h"

using namespace std;

Game::~Game() {
	Enemy::delete_array();
	Arrow::delete_array();
}

void Game::start() {
	Game game;
	game.update_data();
	game.init_loop();
}

void Game::update_data() {
	Level::set_new_level(4);
	Arrow::set_new_level(10);
	Dialogue::set_new_money(50);
	Bomb::set_new_count(10);

	srand(time(0));

	// Смотрим где игрок закончил прошлую игру
	if (Level::get_current_level() <= 0) {
		init_first_start();
	}
	else if (Level::get_current_level() > 10) {
		init_first_start();
	}
	else {
		init_from_saved_state();
	}

	Castle::read_castle();
	Dialogue::read_princess();
	Dialogue::read_blacksmith();
}

void Game::init_loop() {
	while (run) {
		if (check_exit_requested()) break;
		if (!handle_resize()) continue;

		switch (mode) {
		case FirstTime:
			process_first_time();
			break;
		case Castle:
			process_castle();
			break;
		case Battle:
			process_battle();
			break;
		}

		Sleep(15);
		counter++;
		move_cursor(0, 0);
	}
}

bool Game::check_exit_requested() {
	// Если нажата Esc выходим из цикла
	if (check_esc_button()) {
		beautiful_clear_all(1);
		run = false;
		return true;
	}
	return false;
}

bool Game::handle_resize() const {
	// Чиним если был выход из полноэкранного режима
	if (!check_console_size_changes()) {
		clear_all();
		Level::print_level(is_level_passed);
		return false;
	}
	return true;
}

void Game::process_first_time() {
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if (player_attack_timer <= 0) {
			Arrow::init_new_arrow(player);
			player_attack_timer = 12;
		}
	}

	if (player_attack_timer > 0) player_attack_timer--;

	process_player(player);
	Player::print_help();

	Arrow::process_arrows();

	if (player.player_y <= 0) {
		mode = Battle;
		player.player_y = get_console_height() - 1;
		clear_all();
	}
}

void Game::process_castle() {
	Castle::print_castle(player);

	if (player.is_player_on_door(Castle::find_door_index(), Castle::door_y_pos, 2)) {
		if (can_update_level) {
			Dialogue::money_up(15);
			can_update_level = false;
			Level::level_up();
			is_level_passed = false;
		}
		Dialogue::loop();
		if (End::is_end()) {
			Greeting::print_end();
			End::process_end();
			run = false;
			return;
		}
		player.player_y += 1;
		Level::print_level(is_level_passed);
	}

	process_player(player, Purple);

	if (player.player_y >= get_console_height() - 5) {
		mode = Battle;
		Level::wave_timer = 0;
		wave = 1;
		player.player_y = 1;
		beautiful_clear_all(1);
		Level::print_level(is_level_passed);
	}
}

void Game::process_battle() {
	if (Level::wave_timer == 0) {
		Level::init_level(wave++, player);
	}

	if (Level::wave_timer > -1) {
		Level::wave_timer--;
	}
	else if (Enemy::enemies_array_size == 0) {
		is_level_passed = true;
		Level::print_level(is_level_passed);
	}
	Level::print_timer();

	process_enemies();

	if (is_player_die) {
		handle_player_death();
		return;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		if (player_attack_timer <= 0) {
			Arrow::init_new_arrow(player);
			player_attack_timer = 12;
		}
	}

	if (player_attack_timer > 0) player_attack_timer--;

	Arrow::process_arrows();
	Arrow::print_arrow_array_size();
	Bomb::process_bomb();

	process_player(player);

	if (player.player_y <= 0 && Enemy::enemies_array_size == 0 && Level::wave_timer < 0) {
		mode = Castle;
		player.player_y = 37;
		player.player_x = 76;
		can_update_level = true;
		Arrow::delete_array();
		clear_all();
		Level::print_level(is_level_passed);
	}
}

void Game::process_enemies() {
	if (counter % 4 == 0 && counter != 0) {
		for (size_t i = 0; i < Enemy::enemies_array_size; i++) {
			if (Enemy::enemies[i].is_enemy_on_player(player)) {
				killer_id = i;
				is_player_die = true;
			}
			Enemy::enemies[i].clear_enemy();
			Enemy::enemies[i].save_old_cords();
		}
		for (int i = 0; i < Enemy::enemies_array_size; i++) {
			if (is_player_die) {
				Enemy::enemies[killer_id].print_all();
				break;
			}
			Enemy::enemies[i].print_all();
			Enemy::enemies[i].move(player, 2, 1);
		}
	}
	Enemy::check_merge_all();
}

void Game::handle_player_death() {
	string s = "SPACE (Enter/Esc)";
	while (!(GetAsyncKeyState(VK_RETURN) & 0x8000
		|| GetAsyncKeyState(VK_SPACE) & 0x8000
		|| GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
		move_cursor(get_console_width() / 2 - s.length() / 2 + 2, get_console_height() - 1);
		cout << s;
		Sleep(50);
	}
	mode = Castle;
	Enemy::delete_array();
	Arrow::delete_array();
	is_player_die = false;
	player.player_x = 75;
	player.player_y = 27;
	clear_all();
	Level::print_level(false);
}

void Game::process_player(Player& player, const Color color) const {
	if (counter % 2 == 0) {
		if (mode == Castle) player.player_move(1, 1, Castle::can_move_castle);
		else player.player_move(2, 1);
		player.player_clear();
	}
	player.player_print(color);
}

void Game::init_first_start() {
	Level::set_new_level(0);
	Arrow::set_new_level(1);
	Bomb::set_new_count(0);
	mode = FirstTime;
	// Только на нечетном x чтобы мог по правому краю впритык лазить
	player = Player(get_console_width() / 2, get_console_height() / 2);
	Greeting::greeting();
}

void Game::init_from_saved_state() {
	mode = Castle;
	player = Player(75, 27);
	Level::print_level(false);
}