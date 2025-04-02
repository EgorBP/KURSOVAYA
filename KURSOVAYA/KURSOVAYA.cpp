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
	Sleep(80);
	simulateF11();
	disableMouseSelection();

	// !!!!! ЧТОБЫ ДИНОЗАВР ЗАЛЕЗАЛ МОРДОЙ ПО КРАЯМ ЕГО НУЖНО СОЗДАВАТЬ ТОЛЬКО НА НЕЧЕТНЫХ ПОЗИЦИЯХ
	// ИНАЧЕ ОН ЛИБО БУДЕТ ЗАЛЕЗАТЬ ЗА ГНАНИЦУ ИЛИ НЕ ДОСТАНЕТ ДО ИГРОКА С ПРАВОЙ СТОРОНЫ !!!!!
	// p.s это нужно если его координаты перемещения по x = 2
	const int size = 50, bullets = 25;
	Enemy* enemies[size]{ nullptr };
	Arrow* arrows[bullets]{ nullptr };

	enemies[3] = new Enemy{ 101, 25 };
	enemies[4] = new Enemy{ 101, 25 };
	enemies[7] = new Enemy{ 81, 20 };

	// Только на нечетном x чтобы мог по правому краю впритык лазить
	Player player = Player(77, 25);

	bool flag_end_game = false;
	int killer_id;
	long long counter = 0;

	while (!flag_end_game) {
		cout << counter;
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}


		// ДИНО
		if (counter % 4 == 0 && counter != 0) {
			for (int i = 0; i < size; i++) {
				if (enemies[i] != nullptr) {
					// Проверяем всех дино на то достигли они игрока или нет
					if (enemies[i]->is_enemy_on_player(player)) {
						killer_id = i;
						flag_end_game = true;
					}
					// Очищаем всех перед отрисовкой чтобы при перемещении одного
					// не очистился другой на позиции близкой к текущему
					enemies[i]->clear_enemy();
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
					enemies[i]->move(player , 1, 1);
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
					Sleep(100);
				}
				break;
			}
			// Слияние дино
			Enemy::check_merge_all(enemies, size);
		}


		// ПУЛЯ
		if (counter % 6 == 0) {
			// Создание пули
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				// Ищем первую пустую позицию в которую запишем пулю
				// Если делать отдельную ф-цию она будет принимать 6 аргументов
				for (int i = 0; i < 25; i++) {
					if (arrows[i] == nullptr) {
						arrows[i] = new Arrow(player);
						break;
					}
				}

			}
		}
		// Перемещение пули
		Arrow::arrow_move(arrows, enemies, bullets, size);


		// Движение игрока
		if (counter % 2 == 0) {
			player.player_move();
			//move_cursor(0, 0);
		}
		player.player_print();


		// Сервисные действия
		//Sleep(15);
		counter += 1;
		Sleep(15);
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