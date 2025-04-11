#include <iostream>
#include <windows.h>
#include "services.h"
#include "enemies.h"
#include "player.h"
#include "bow.h"
#include "castle.h"
#include "greeting.h"
#include "level.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hideCursor();
	// Чтобы окно успело открыться
	Sleep(100);
	simulateF11();
	// Чтобы успело перйти в полноэкранный режим
	Sleep(300);
	disableMouseSelection();
	srand(time(0));

	Level::set_new_level(1);
	Arrow::set_new_level(2);


	string mode;
	Player player;
	// Смотрим где игрок закончил прошлую игру
	if (Level::get_current_level() < 0 || Level::get_current_level() == 0) {
		Level::set_new_level(0);
		mode = "first_time";
		// Только на нечетном x чтобы мог по правому краю впритык лазить
		player = Player(get_console_width() / 2, get_console_height() / 2);
		//Greeting::greeting();
	}
	else {
		mode = "castle";
		player = Player(75, 27);
		Level::print_level(false);
	}

	//mode = "battle";

	bool flag_end_game = false;
	bool can_update_level = false;
	bool can_change_location = true;
	bool is_level_passed = false;
	int player_attack_timer = 0;
	int intit_wave_timer = 0;
	int wave = 1;
	int killer_id;
	unsigned long long counter = 0;

	while (!flag_end_game) {
		//Beep(1000, 100);

		//cout << counter;
		// Если нажата Esc выходим из цикла
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			flag_end_game = true;
			break;
		}

		// Немного чиним если был выход из полноэкранного режима
		if (!check_console_size_changes()) {
			clear_all();
			Level::print_level(is_level_passed);
		}


		if (mode == "first_time") {
			// Движение игрока
			if (counter % 2 == 0) {
				player.player_move(2, 1);
				player.player_clear();
			}
			// Отрисовка игрока
			player.player_print();

			if (player.player_y <= 0) {
				mode = "battle";
				player.player_y = get_console_height() - 1;
				clear_all();
				continue;
			}
		}


		if (mode == "castle") {
			Castle::print_castle(player);
			if (can_update_level && player.is_player_on_door(Castle::find_door_index(), Castle::door_y_pos, 2)) {
				can_update_level = false;
				Level::level_up();
				is_level_passed = false;
				Level::print_level(is_level_passed);
			}

			// Движение игрока
			player.player_move(1, 1);
			player.player_clear();
			// Отрисовка игрока
			player.player_print("purple");

			// Смена локации
			if (player.player_y >= get_console_height() - 2) {
				mode = "battle";
				intit_wave_timer = 0;
				wave = 1;
				player.player_y = 1;
				clear_all();
				Level::print_level(is_level_passed);
				disableMouseSelection();
				continue;
			}
		}


		if (mode == "battle") {
			// ИНИЦИАЛИЗАТОР
			if (intit_wave_timer == 0) {
				Level::init_level(wave++, player, intit_wave_timer);
			}

			if (intit_wave_timer > -1) {
				intit_wave_timer--;
			}
			else if (intit_wave_timer <= -1 && Enemy::enemies_array_size == 0) {
				is_level_passed = true;
				Level::print_level(is_level_passed);
			}
			Level::print_timer(intit_wave_timer);


			// ДИНО
			if (counter % 4 == 0 && counter != 0) {
				for (size_t i = 0; i < Enemy::enemies_array_size; i++) {
					// Проверяем всех дино на то достигли они игрока или нет
					if (Enemy::enemies[i].is_enemy_on_player(player)) {
						killer_id = i;
						flag_end_game = true;
					}
					// Очищаем всех перед отрисовкой чтобы при перемещении одного
					// не очистился другой на позиции близкой к текущему
					Enemy::enemies[i].clear_enemy();
					Enemy::enemies[i].save_old_cords();
				}
				for (int i = 0; i < Enemy::enemies_array_size; i++) {
					// Если игра закончилась то рисумем только того что съел гг
					if (flag_end_game) {
						Enemy::enemies[killer_id].print();
						break;
					}
					// Если нет то рисуем всех и двигаем
					Enemy::enemies[i].print();
					Enemy::enemies[i].move(player, 2, 1);
				}
			}
			if (flag_end_game) {
				// Чтобы не видить нажатия других символов мы ждем пока юзер нажмет на нужную кнопку,
				// а до этого выводим текст поверх всех напечатанных символов
				while (!(GetAsyncKeyState(VK_RETURN) & 0x8000
					|| GetAsyncKeyState(VK_SPACE) & 0x8000
					|| GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
					move_cursor(0, 0);
					cout << "Поражение, нажмите Space или Enter...";
					Sleep(50);
				}
				mode = "castle";
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

			if (player_attack_timer > 0)
				player_attack_timer--;

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


			if (player.player_y <= 0 && Enemy::enemies_array_size == 0 && intit_wave_timer < 0) {
				mode = "castle";
				player.player_y = 37;
				player.player_x = 76;
				can_update_level = true;
				Arrow::delete_array();
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

	move_cursor(0, 0);
	//system("pause");
	return 0;
}