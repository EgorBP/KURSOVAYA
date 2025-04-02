#include <iostream>
#include <windows.h>
#include "bow.h"
#include "services.h"
#include "enemies.h"

using namespace std;

void Arrow::arrow_clear() const {
    if (arrow_side == '>') clear(arrow_x - 1, arrow_y, 3);
    if (arrow_side == '<') clear(arrow_x - 1, arrow_y, 3);
    if (arrow_side == '^') {
        clear(arrow_x, arrow_y - 0);
        clear(arrow_x, arrow_y - 1);
        clear(arrow_x, arrow_y - 2);
    }
    if (arrow_side == 'V') {
        clear(arrow_x, arrow_y + 2);
        clear(arrow_x, arrow_y + 1);
        clear(arrow_x, arrow_y + 0);
    }
}

bool Arrow::is_arrow_border() const {
    if (arrow_side == '>') return !can_move_border(arrow_x + 1, arrow_y);
    if (arrow_side == '<') return !can_move_border(arrow_x, arrow_y);
    if (arrow_side == '^') return !can_move_border(arrow_x, arrow_y - 2);
    if (arrow_side == 'V') return !can_move_border(arrow_x, arrow_y + 2);
}

void Arrow::print_arrow() const {
    if (arrow_side == '>') {
        move_cursor(arrow_x - 1, arrow_y);
        cout << "*->";
    }
    if (arrow_side == '<') {
        move_cursor(arrow_x - 1, arrow_y);
        cout << "<-*";
    }
    if (arrow_side == '^') {
        move_cursor(arrow_x, arrow_y - 2);
        cout << '^';
        move_cursor(arrow_x, arrow_y - 1);
        cout << '|';
        move_cursor(arrow_x, arrow_y - 0);
        cout << '*';
    }
    if (arrow_side == 'V') {
        move_cursor(arrow_x, arrow_y + 0);
        cout << '*';
        move_cursor(arrow_x, arrow_y + 1);
        cout << '|';
        move_cursor(arrow_x, arrow_y + 2);
        cout << 'V';
    }
}

bool Arrow::is_arrow_on_enemy(const int enemy_x, const int enemy_y) const {
    if (arrow_side == '>') {
        if ((arrow_x + 2 >= enemy_x && arrow_x <= enemy_x + 9) && (arrow_y <= enemy_y + 3 && arrow_y >= enemy_y)) return true;
    }
    if (arrow_side == '<') {
        if ((arrow_x - 2 >= enemy_x && arrow_x <= enemy_x + 11) && (arrow_y <= enemy_y + 3 && arrow_y >= enemy_y)) return true;
    }
    if (arrow_side == '^') {
        if ((arrow_x >= enemy_x && arrow_x <= enemy_x + 9) && (arrow_y <= enemy_y + 6 && arrow_y >= enemy_y - 3)) return true;
    }
    if (arrow_side == 'V') {
        if ((arrow_x >= enemy_x && arrow_x <= enemy_x + 9) && (arrow_y <= enemy_y + 6 && arrow_y >= enemy_y - 3)) return true;
    }
    return false;
}

void Arrow::arrow_move(Arrow** arrows, Enemy** enemies, const int bullets, const int size) {
    for (int i = 0; i < bullets; i++) {
        if (arrows[i]) {
            move_cursor(0, 1);
            bool end = false;
            arrows[i]->arrow_clear();
            for (int i_enemy = 0; i_enemy < size; i_enemy++) {
                if (enemies[i_enemy]) {
                    if (arrows[i]->is_arrow_on_enemy(enemies[i_enemy]->enemy_upper_left_x, enemies[i_enemy]->enemy_upper_left_y)) {
                        enemies[i_enemy]->merge(-1);
                        arrows[i] = nullptr;
                        end = true;
                        break;
                    }
                }
            }
            if (end) break;

            if (arrows[i]->arrow_side == '<') arrows[i]->arrow_x -= 2;
            else if (arrows[i]->arrow_side == '>') arrows[i]->arrow_x += 2;
            else if (arrows[i]->arrow_side == '^') arrows[i]->arrow_y--;
            else if (arrows[i]->arrow_side == 'V') arrows[i]->arrow_y++;
            move_cursor(0, 0);
            if (arrows[i]->is_arrow_border()) {
                arrows[i] = nullptr;
                continue;
            }
            arrows[i]->print_arrow();
        }
    }

}