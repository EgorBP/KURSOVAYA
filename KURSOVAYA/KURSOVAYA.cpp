#include <iostream>
#include <windows.h>
#include "services.h"
#include "decoration.h"
#include "player.h"
#include "enemies.h"

using namespace std;


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hideCursor();
	Sleep(80);
	simulateF11();
	disableMouseSelection();

	// !!!!! ЧТОБЫ ДИНОЗАВР ЗАЛЕЗАЛ МОРДОЙ ПО КРАЯМ ЕГО НУЖНО СОЗДАВАТЬ ТОЛЬКО НА НЕЧЕТНЫХ ПОЗИЦИЯХ ИНАЧЕ ОН ЛИБО БУДЕТ ЗАЛЕЗАТЬ ЗА ГНАНИЦУ ИЛИ НЕ ДОСТАНЕТ ДО ИГРОКА С ПРАВОЙ СТОРОНЫ !!!!!
	const int size = 50;
	Enemy* enemies[size]{};

	//enemies[0] = new Enemy{ 1, 10 };
	//enemies[1] = new Enemy{ 131, 30 };
	enemies[7] = new Enemy{ 81, 20 };
	enemies[6] = new Enemy{ 81, 40 };

	// Только на нечетном x чтобы мог по правому краю впритык лазить
	int player_x = 77;
	int player_y = 25;
	char player_type;

	bool flag = false;
	int killer_id;

	int parity = 0;  // Четность
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}

		// Перемещение дино
		if (parity % 2 != 0) {
			for (int i = 0; i < size; i++) {
				if (enemies[i] != nullptr) {
					if (enemies[i]->is_enemy_on_player(player_x, player_y)) {
						killer_id = i;
						//flag = true;
					}
					enemies[i]->clear_enemy();
				}
			}
			for (int i = 0; i < size; i++) {
				if (flag) {
					enemies[killer_id]->print();
					break;
				}
				if (enemies[i] != nullptr) {
					enemies[i]->print();
					enemies[i]->move(player_x, player_y, 1, 1);
				}
			}
			if (flag) {
				break;
			}

			// Слияние дино
			for (int i = 0; i < size; i++) {
				if (enemies[i]) {
					int x_main = enemies[i]->enemy_upper_left_x;
					int y_main = enemies[i]->old_enemy_upper_left_y;

					for (int i_checker = 0; i_checker < size; i_checker++) {
						if (enemies[i_checker] && i != i_checker) {

							int x_other = enemies[i_checker]->enemy_upper_left_x;
							int y_other = enemies[i_checker]->enemy_upper_left_y;

							if (abs(x_main - x_other) < 9 && abs(y_main - y_other) < 3) {
								enemies[i_checker]->merge(enemies[i]->level); // Повышаем уровень
								enemies[i]->clear_enemy();                    // Очищаем перед удалением
								enemies[i_checker]->clear_enemy();            // Очищаем и рисуем заново в этой же итерации чтобы создать
								enemies[i_checker]->print();                  //  эффкт переваривания (задержка) и перебить очищение от удаленного
								enemies[i] = nullptr;                         // Удаляем
							}
						}
					}
				}
			}

			parity -= 1;
		}
		else {
			parity += 1;
		}

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			//piy(player_x, player_y);
		}

		// Движение игрока
		set_color(2);
		player_move(player_x, player_y, player_type);
		move_cursor(0, 0);
		set_color(7);

		//Sleep(80);
		Sleep(50);
		move_cursor(0, 0);
	}

	for (int i = 0; enemies[i] != nullptr && i < size; i++) {
		delete enemies[i];
	}

	//StopMouseTracking();
	move_cursor(0, 0);
	return 0;
}