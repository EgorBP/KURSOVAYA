#include <iostream>
#include <windows.h>
#include "services.h"

using namespace std;

void piy_clear(const int bullet_x, const int bullet_y, const char bullet_side) {
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

bool is_piy_border(const int x, const int y, const char side) {
    if (side == '>') return !can_move_border(x + 1, y);
    if (side == '<') return !can_move_border(x, y);
    if (side == '^') return !can_move_border(x, y - 2);
    if (side == 'V') return !can_move_border(x, y + 2);
}

void print_bullet(const int bullet_x, const int bullet_y, const char bullet_side) {
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

void player_print(const int player_x, const int player_y, const char cursor_type) {
    move_cursor(player_x, player_y);
    set_color(2);
    cout << cursor_type;
    set_color(7);
}

void player_move(int& x, int& y, char& cursor_type) {
    clear(x, y);
    if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_border(x - 2, y - 1)) { // Вверх и влево
        y -= 1;
        x -= 2;
    }
    else if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_border(x + 2, y - 1)) { // Вверх и вправо
        y -= 1;
        x += 2;
    }
    else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_border(x - 2, y + 1)) { // Вниз и влево
        y += 1;
        x -= 2;
    }
    else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_border(x + 2, y + 1)) { // Вниз и вправо
        y += 1;
        x += 2;
    }
    else if (GetAsyncKeyState('W') & 0x8000 && can_move_border(x, y - 1)) { // Только вверх
        y -= 1;
    }
    else if (GetAsyncKeyState('S') & 0x8000 && can_move_border(x, y + 1)) { // Только вниз
        y += 1;
    }
    else if (GetAsyncKeyState('A') & 0x8000 && can_move_border(x - 2, y)) { // Только влево
        x -= 2;
    }
    else if (GetAsyncKeyState('D') & 0x8000 && can_move_border(x + 2, y)) { // Только вправо
        x += 2;
    }

    POINT p;
    HWND hwnd = GetConsoleWindow();
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);
    double x_pos = (double)p.x / 9.7;       // Переводим позицию мыши в координаты консоли ( +-1 )
    double y_pos = (double)p.y / 17.6;

    //std::cout << "Mouse X: " << x_pos << " Y: " << y_pos << std::endl;
    //cout << x << ' ' << y;

    // Так как расстояние между строками и столбцами не совпадает для корректного изменения 
    // требуется немного увеличить расстояние вертикальных курсоров
    if ((y - y_pos) * 1.9 >= abs(x - x_pos)) {
        cursor_type = '^';
    }
    else if ((y_pos - y) * 1.5 >= abs(x - x_pos)) {
        cursor_type = 'V';
    }
    else if ((x_pos - x) >= abs(y - y_pos)) {
        cursor_type = '>';
    }
    else if ((x - x_pos) >= abs(y - y_pos)) {
        cursor_type = '<';
    }
}