#include <iostream>
#include <windows.h>
#include "services.h"
#include "decoration.h"
#include "player.h"
#include "enemies.h"
#include "bow.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hideCursor();
	// Чтобы окно успело открыться
	Sleep(100);
	simulateF11();
	// Чтобы успело перйти в полноэкранный режим
	Sleep(50);
	disableMouseSelection();

	// !!!!! ЧТОБЫ ДИНОЗАВР ЗАЛЕЗАЛ МОРДОЙ ПО КРАЯМ ЕГО НУЖНО СОЗДАВАТЬ ТОЛЬКО НА НЕЧЕТНЫХ ПОЗИЦИЯХ
	// ИНАЧЕ ОН ЛИБО БУДЕТ ЗАЛЕЗАТЬ ЗА ГНАНИЦУ ИЛИ НЕ ДОСТАНЕТ ДО ИГРОКА С ПРАВОЙ СТОРОНЫ !!!!!
	// p.s это нужно если его координаты перемещения по x = 2
	const int size = 50, bullets = 25;
	Enemy* enemies[size]{ nullptr };
	Arrow* arrows[bullets]{ nullptr };

	enemies[3] = new Enemy{ 101, 25 };
	enemies[4] = new Enemy{ 101, 15 };
	enemies[7] = new Enemy{ 81, 20 };

	// Только на нечетном x чтобы мог по правому краю впритык лазить
	Player player = Player(77, 25);

	//string mode = "battle";
	string mode = "castle";

	int player_attack_timer = 0;
	bool flag_end_game = false;
	int killer_id;
	int not_empty_elements = 0;
	long long counter = 0;

	while (!flag_end_game) {
		//cout << counter;
		// Если нажата Esc выходим из цикла
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}


		if (mode == "castle" ) {
			move_cursor();
			print_castle();

			if (player.player_y >= 45) {
				mode = "battle";
				player.player_y = 1;
				clear_all();
				continue;
			}
		}


		if (mode == "battle") {
			// ДИНО
			if (counter % 4 == 0 && counter != 0) {
				not_empty_elements = 0;
				for (int i = 0; i < size; i++) {
					if (enemies[i] != nullptr) {
						not_empty_elements++;
						// Проверяем всех дино на то достигли они игрока или нет
						if (enemies[i]->is_enemy_on_player(player)) {
							killer_id = i;
							flag_end_game = true;
						}
						// Очищаем всех перед отрисовкой чтобы при перемещении одного
						// не очистился другой на позиции близкой к текущему
						enemies[i]->clear_enemy();
						enemies[i]->save_old_cords();
					}
				}
				for (int i = 0; i < size; i++) {
					// Если игра закончилась то рисумем только того что съел гг
					if (flag_end_game) {
						enemies[killer_id]->print();
						break;
					}
					// Если нет то рисуем всех и двигаем
					if (enemies[i] != nullptr) {
						enemies[i]->print();
						enemies[i]->move(player, 1, 1);
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
					break;
				}
				// Слияние дино
				Enemy::check_merge_all(enemies, size);
			}


			// ПУЛЯ
			// Создание пули
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				if (player_attack_timer <= 0) {
					Arrow::init_arrow_in_array(arrows, player, size);
					player_attack_timer = 12;
				}
			}

			if (player_attack_timer > 0)
				player_attack_timer--;

			// Перемещение пули и там же уменьшение уровня динозавра или удаление
			Arrow::arrow_move(arrows, enemies, bullets, size);


			if (player.player_y == 0 && not_empty_elements == 0) {
				mode = "castle";
				player.player_y = 44;
				clear_all();
				continue;
			}
		}

		// Движение игрока
		player.player_print();
		if (counter % 2 == 0) {
			player.player_move();
		}
		player.player_print();


		// Сервисные действия
		//Sleep(15);
		Sleep(15);
		counter += 1;
		player.player_print();
		move_cursor(0, 0);
	}

	// Освобождаем динамические массивы
	for (int i = 0; i < size; i++) {
		delete enemies[i];
	}
	for (int i = 0; i < bullets; i++) {
		delete arrows[i];
	}

	move_cursor(0, 0);
	//system("pause");
	return 0;
}