#include <iostream>
#include <windows.h>
#include "services.h"
#include "enemies.h"
#include "player.h"
#include "bow.h"
#include "castle.h"
#include "greeting.h"
#include "level.h"
#include "game.h"
#include "dialogue.h"

using namespace std;

void Game::start() {
	srand(time(0));
	Game game;
	game.update_data();
	game.init_loop();
}

void Game::update_data() {
	Level::set_new_level(10);
	Arrow::set_new_level(10);
	//Dialogue::set_new_money(0);

	// Смотрим где игрок закончил прошлую игру
	if (Level::get_current_level() < 0 || Level::get_current_level() == 0) {
		Level::set_new_level(0);
		mode = Mode::FirstTime;
		// Только на нечетном x чтобы мог по правому краю впритык лазить
		player = Player(get_console_width() / 2, get_console_height() / 2);
		//Greeting::greeting();
	}
	else {
		mode = Mode::Castle;
		player = Player(75, 27);
		Level::print_level(false);
	}
}

void Game::init_loop() {
	while (run) {
		//cout << counter;
		// Если нажата Esc выходим из цикла
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			beautiful_clear_all(1);
			run = false;
			break;
		}

		// Чиним если был выход из полноэкранного режима
		if (!check_console_size_changes()) {
			clear_all();
			Level::print_level(is_level_passed);
		}


		if (mode == Mode::FirstTime) {
			// Движение игрока
			if (counter % 2 == 0) {
				player.player_move(2, 1);
				player.player_clear();
			}
			// Отрисовка игрока
			player.player_print();

			if (player.player_y <= 0) {
				mode = Mode::Battle;
				player.player_y = get_console_height() - 1;
				clear_all();
				continue;
			}
		}


		else if (mode == Mode::Castle) {
			Castle::print_castle(player);
			if (player.is_player_on_door(Castle::find_door_index(), Castle::door_y_pos, 2)) {
				if (can_update_level) {
					Dialogue::money_up(15);
					can_update_level = false;
					Level::level_up();
					is_level_passed = false;
				}

				Dialogue::loop();
				player.player_y += 1;
				Level::print_level(is_level_passed);
			}

			// Движение игрока
			player.player_move(1, 1);
			player.player_clear();
			// Отрисовка игрока
			player.player_print(Color::Purple);

			// Смена локации
			if (player.player_y >= get_console_height() - 2) {
				mode = Mode::Battle;
				Level::wave_timer = 0;
				wave = 1;
				player.player_y = 1;
				beautiful_clear_all(1);
				Level::print_level(is_level_passed);
				disableMouseSelection();
				continue;
			}
		}


		else if (mode == Mode::Battle) {
			// ИНИЦИАЛИЗАТОР
			if (Level::wave_timer == 0) {
				Level::init_level(wave++, player);
			}

			if (Level::wave_timer > -1) {
				Level::wave_timer--;
			}
			else if (Level::wave_timer <= -1 && Enemy::enemies_array_size == 0) {
				is_level_passed = true;
				Level::print_level(is_level_passed);
			}
			Level::print_timer();


			// ДИНО
			if (counter % 4 == 0 && counter != 0) {
				for (size_t i{ 0 }; i < Enemy::enemies_array_size; i++) {
					// Проверяем всех дино на то достигли они игрока или нет
					if (Enemy::enemies[i].is_enemy_on_player(player)) {
						killer_id = i;
						is_player_die = true;
					}
					// Очищаем всех перед отрисовкой чтобы при перемещении одного
					// не очистился другой на позиции близкой к текущему
					Enemy::enemies[i].clear_enemy();
					Enemy::enemies[i].save_old_cords();
				}
				for (int i = 0; i < Enemy::enemies_array_size; i++) {
					// Если игра закончилась то рисумем только того что съел гг
					if (is_player_die) {
						Enemy::enemies[killer_id].print_all();
						break;
					}
					// Если нет то рисуем всех и двигаем
					Enemy::enemies[i].print_all();
					Enemy::enemies[i].move(player, 2, 1);
				}
			}
			if (is_player_die) {
				// Чтобы не видить нажатия других символов мы ждем пока юзер нажмет на нужную кнопку,
				// а до этого выводим текст поверх всех напечатанных символов
				while (!(GetAsyncKeyState(VK_RETURN) & 0x8000
					|| GetAsyncKeyState(VK_SPACE) & 0x8000
					|| GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
					move_cursor(0, 0);
					cout << "Поражение, нажмите Space или Enter...";
					Sleep(50);
				}
				mode = Mode::Castle;
			}
			// Слияние дино
			Enemy::check_merge_all();


			// ПУЛЯ
			// Создание пули
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				if (player_attack_timer <= 0) {
					Arrow::init_new_arrow(player);
					player_attack_timer = 12;
				}
			}

			if (player_attack_timer > 0) {
				player_attack_timer--;
			}

			// Перемещение пули и там же уменьшение уровня динозавра или удаление
			Arrow::process_arrows();
			Arrow::print_arrow_array_size();


			// Движение игрока
			if (counter % 2 == 0) {
				player.player_move(2, 1);
				player.player_clear();
			}
			// Отрисовка игрока
			player.player_print();


			if (player.player_y <= 0 && Enemy::enemies_array_size == 0 && Level::wave_timer < 0) {
				mode = Mode::Castle;
				player.player_y = 37;
				player.player_x = 76;
				can_update_level = true;
				Arrow::delete_array();
				//beautiful_clear_all(0, '#');
				clear_all();
				Level::print_level(is_level_passed);
				continue;
			}
		}


		// Сервисные действия
		//Sleep(15);
		Sleep(15);
		counter++;
		move_cursor(0, 0);
	}

	// Освобождаем динамические массивы
	Enemy::delete_array();
	Arrow::delete_array();
}