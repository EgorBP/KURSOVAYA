#include <iostream>
#include <windows.h>
#include "bow.h"
#include "services.h"
#include "enemies.h"
#include "player.h"

using namespace std;

size_t Arrow::arrows_array_size = 0;
Arrow* Arrow::arrows = nullptr;

void Arrow::init_new_arrow(Player& player) {
    // Динамически меняем размер
    Arrow* new_array = new Arrow[arrows_array_size + 1];

    for (size_t i = 0; i < arrows_array_size; i++) { // копируем старые стрелы
        new_array[i] = arrows[i];
    }

    new_array[arrows_array_size] = Arrow(player);

    delete[] arrows;
    arrows = new_array;
    arrows_array_size++;
}

void Arrow::rebuild_array_without_element(const size_t index) {
    //if (arrows_array_size == 0) return;

    Arrow* new_array = new Arrow[arrows_array_size - 1];
    for (size_t i = 0, j = 0; i < arrows_array_size; i++) {
        if (i != index) {
            new_array[j] = arrows[i];
            j++;
        }
    }

    delete[] arrows;
    arrows = new_array;
    arrows_array_size--;
}

void Arrow::process_arrows() {
    for (int i = 0; i < arrows_array_size; i++) {
        bool to_destroy = false;
        arrows[i].arrow_clear();

        // Проверка на столкновение с врагами
        for (int i_enemy = 0; i_enemy < Enemy::enemies_array_size; i_enemy++) {
            if (arrows[i].is_arrow_on_enemy(Enemy::enemies[i_enemy].enemy_upper_left_x, Enemy::enemies[i_enemy].enemy_upper_left_y)) {
                Enemy::enemies[i_enemy].merge(-1);
                if (Enemy::enemies[i_enemy].level <= 0) {
                    Enemy::enemies[i_enemy].clear_enemy();
                    Enemy::rebuild_array_without_element(i_enemy);
                }
                to_destroy = true;
                break;  // Прерываем цикл по врагам, но не внешний!
            }
        }

        // Движение стрелы
        if (arrows[i].arrow_side == '<') arrows[i].arrow_x -= 2;
        else if (arrows[i].arrow_side == '>') arrows[i].arrow_x += 2;
        else if (arrows[i].arrow_side == '^') arrows[i].arrow_y--;
        else if (arrows[i].arrow_side == 'V') arrows[i].arrow_y++;

        if (to_destroy || arrows[i].is_arrow_border()) {
            rebuild_array_without_element(i);
            i--;
            continue;
        }

        arrows[i].print_arrow();
    }
}

void Arrow::print_arrow_array_size() {
    move_cursor(0, get_console_height() - 1);
    cout << arrows_array_size;
}

void Arrow::delete_array() {
    delete[] arrows;
    arrows = nullptr;
    arrows_array_size = 0;
}


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
    if (arrow_side == '<') return !can_move_border(arrow_x - 1, arrow_y);
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
