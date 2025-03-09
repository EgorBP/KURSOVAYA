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

    enemies[0] = new Enemy{ 1, 10 };
    enemies[1] = new Enemy{ 131, 30 };
    enemies[2] = new Enemy{ 51, 20 };


    int player_x = 77;
    int player_y = 25;
    char player_type;

    int parity = 0;  // Четность
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        // Перемещение дино
        if (parity % 2 != 0) {
            for (int i = 0; i < size; i++) {
                if (enemies[i] != nullptr) {
                    int level = enemies[i]->level, color = 7;  // Белый
                    if (level == 1) {}
                    else if (level == 2) color = 6; // Желтый
                    else if (level == 3) color = 4; // Красный
                    else if (level == 4) color = 6; // Пурпурный
                    else color = 6; //
                    set_color(color);
                    enemies[i]->clear_enemy();
                    enemies[i]->print();
                    enemies[i]->move(player_x, player_y, 1, 1);
                }
            }
            // Слияние дино
            for (int i = 0; i < size; i++) {
                if (enemies[i]) {
                    int x_main = enemies[i]->enemy_upper_left_x;
                    int y_main = enemies[i]->enemy_upper_left_y;

                    for (int i_checker = 0; i_checker < size; i_checker++) {
                        if (enemies[i_checker] && i != i_checker) {

                            int x_other = enemies[i_checker]->enemy_upper_left_x;
                            int y_oyter = enemies[i_checker]->enemy_upper_left_y;

                            if (abs(x_main - x_other) < 9) {
                                enemies[i_checker]->merge(enemies[i]->level);
                                enemies[i]->clear_enemy();
                                enemies[i] = nullptr;
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
        
        set_color(2);
        player_move(player_x, player_y, player_type);
        move_cursor(0, 0);
        set_color(7);

        //Sleep(80);
        Sleep(20);
        move_cursor(0, 0);
    }

    for (int i = 0; enemies[i] != nullptr && i < size; i++) {
        delete enemies[i];
    }
    //delete[] x_cords;
    //delete[] y_cords;

    return 0;
}