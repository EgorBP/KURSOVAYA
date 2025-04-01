#include <iostream>
#include <windows.h>
#include "services.h"
#include "enemies.h"

using namespace std;

void arrow_clear(const int bullet_x, const int bullet_y, const char bullet_side) {
    if (bullet_side == '>') clear(bullet_x - 1, bullet_y, 3);
    if (bullet_side == '<') clear(bullet_x - 1, bullet_y, 3);
    if (bullet_side == '^') {
        clear(bullet_x, bullet_y - 0);
        clear(bullet_x, bullet_y - 1);
        clear(bullet_x, bullet_y - 2);
    }
    if (bullet_side == 'V') {
        clear(bullet_x, bullet_y + 2);
        clear(bullet_x, bullet_y + 1);
        clear(bullet_x, bullet_y + 0);
    }
}

bool is_arrow_border(const int x, const int y, const char side) {
    if (side == '>') return !can_move_border(x + 1, y);
    if (side == '<') return !can_move_border(x, y);
    if (side == '^') return !can_move_border(x, y - 2);
    if (side == 'V') return !can_move_border(x, y + 2);
}

void print_arrow(const int bullet_x, const int bullet_y, const char bullet_side) {
    //cout << bullet_side;
    if (bullet_side == '>') {
        move_cursor(bullet_x - 1, bullet_y);
        cout << "*->";
    }
    if (bullet_side == '<') {
        move_cursor(bullet_x - 1, bullet_y);
        cout << "<-*";
    }
    if (bullet_side == '^') {
        move_cursor(bullet_x, bullet_y - 2);
        cout << '^';
        move_cursor(bullet_x, bullet_y - 1);
        cout << '|';
        move_cursor(bullet_x, bullet_y - 0);
        cout << '*';
    }
    if (bullet_side == 'V') {
        move_cursor(bullet_x, bullet_y + 0);
        cout << '*';
        move_cursor(bullet_x, bullet_y + 1);
        cout << '|';
        move_cursor(bullet_x, bullet_y + 2);
        cout << 'V';
    }
}

bool is_arrow_on_enemy(const int bullet_x, const int bullet_y, const int enemy_x, const int enemy_y, const char side) {
    if (side == '>') {
        if ((bullet_x + 2 >= enemy_x && bullet_x <= enemy_x + 9) && (bullet_y <= enemy_y + 3 && bullet_y >= enemy_y)) return true;
    }
    if (side == '<') {
        if ((bullet_x - 2 >= enemy_x && bullet_x <= enemy_x + 11) && (bullet_y <= enemy_y + 3 && bullet_y >= enemy_y)) return true;
    }
    if (side == '^') {
        if ((bullet_x >= enemy_x && bullet_x <= enemy_x + 9) && (bullet_y <= enemy_y + 6 && bullet_y >= enemy_y - 3)) return true;
    }
    if (side == 'V') {
        if ((bullet_x >= enemy_x && bullet_x <= enemy_x + 9) && (bullet_y <= enemy_y + 6 && bullet_y >= enemy_y - 3)) return true;
    }
    return false;
}

void arrow_move(char** bullet_side, int** bullet_cord, Enemy** enemies, const int bullets, const int size) {
    // Движение пули
    for (int i = 0; i < bullets; i++) {
        if (bullet_side[i]) {
            bool end = false;
            const char side = *bullet_side[i];
            int& x = bullet_cord[i][0];
            int& y = bullet_cord[i][1];
            arrow_clear(x, y, side);
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
            if (is_arrow_border(x, y, side)) {
                bullet_side[i] = nullptr;
                bullet_cord[i] = nullptr;
                continue;
            }
            print_arrow(x, y, side);
        }
    }

}