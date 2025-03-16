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
	const int size = 50, bullets = 25;
	Enemy* enemies[size]{};
	int* bullet_cord[bullets]{};
	char* bullet_side[bullets]{};

	//enemies[0] = new Enemy{ 1, 10 };
	enemies[1] = new Enemy{ 101, 30 };
	enemies[2] = new Enemy{ 101, 30 };
	enemies[3] = new Enemy{ 101, 25 };
	enemies[4] = new Enemy{ 101, 25 };
	enemies[7] = new Enemy{ 81, 20 };
	//enemies[6] = new Enemy{ 81, 40 };

	// Только на нечетном x чтобы мог по правому краю впритык лазить
	int player_x = 77;
	int player_y = 25;
	char player_type = '^';

	bool flag_end_game = false;
	int killer_id;

	int parity = 0;  // Четность
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}

		// Перемещение дино
		if (parity % 4 == 0 && parity != 0) {
			for (int i = 0; i < size; i++) {
				if (enemies[i] != nullptr) {

					if (enemies[i]->is_enemy_on_player(player_x, player_y)) {
						killer_id = i;
						flag_end_game = true;
					}
					enemies[i]->clear_enemy();
				}
			}
			for (int i = 0; i < size; i++) {
				if (flag_end_game) {
					enemies[killer_id]->print();
					break;
				}
				if (enemies[i] != nullptr) {
					enemies[i]->print();
					enemies[i]->move(player_x, player_y, 1, 1);
				}
			}
			if (flag_end_game) {
				move_cursor(0, 0);
				cout << "Поражение";
				cin.get();
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

			//parity -= 8;
		}
		//else {
			parity += 1;
			//cout << parity;
		//}


		if (parity % 6 == 0) {
			// Создание пули
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				// Ищем первую пустую позицию в которую запишем пулю
				int free_pos = 0;
				for (int i = 0; i < 25; i++) {
					if (bullet_cord[i] == nullptr) {
						free_pos = i;
						bullet_side[i] = new char(player_type);
						bullet_cord[i] = new int[2] {player_x, player_y};
						break;
					}
				}

			}
		}
		// Движение пули
		for (int i = 0; i < bullets; i++) {
			if (bullet_side[i]) {
				bool end = false;
				const char side = *bullet_side[i];
				int& x = bullet_cord[i][0];
				int& y = bullet_cord[i][1];
				piy_clear(x, y, side);
				for (int i_enemy = 0; i_enemy < size; i_enemy++) {
					if (enemies[i_enemy] != nullptr) {
						if (is_arrow_on_enemy(x, y, enemies[i_enemy]->enemy_upper_left_x, enemies[i_enemy]->enemy_upper_left_y, side)) {
							enemies[i_enemy]->merge(-1);
							bullet_side[i] = nullptr;
							bullet_cord[i] = nullptr;
							end = true;
							break;
						}
					}
				}
				if (end) break;

				if (side == '<') x -= 2;
				else if (side == '>') x += 2;
				else if (side == '^') y--;
				else if (side == 'V') y++;
				move_cursor(0, 0);
				if (is_piy_border(x, y, side)) {
					bullet_side[i] = nullptr;
					bullet_cord[i] = nullptr;
					continue;
				}
				print_bullet(x, y, side);
			}
		}

		// Движение игрока
		if (parity % 2 == 0) {
			player_move(player_x, player_y, player_type);
			move_cursor(0, 0);
		}
		player_print(player_x, player_y, player_type);

		//Sleep(15);
		Sleep(15);
		move_cursor(0, 0);
	}
	
	// Освобождаем динамические массивы
	for (int i = 0; i < size; i++) {
		delete enemies[i];
	}
	for (int i = 0; i < bullets; i++) {
		delete bullet_cord[i];
		delete bullet_side[i];
	}
	move_cursor(0, 0);
	//system("pause");
	return 0;
}