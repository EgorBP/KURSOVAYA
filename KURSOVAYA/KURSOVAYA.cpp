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
    Enemy enemy = { 50, 24 };

    int player_x = 78;
    int player_y = 25;
    char player_type = 'V';

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        //system("cls");
        //print_castle();
        set_color(2);
        player_move(player_x, player_y, player_type);
        move_cursor(0, 0);
        set_color(7);
        enemy.clear_enemy();
        enemy.print();
        enemy.move(player_x, player_y);

        Sleep(80);
        move_cursor(0, 0);
    }

    //system("pause");
    return 0;
}