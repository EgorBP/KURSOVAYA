#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int get_console_width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;
}

int get_console_height() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;
}

bool check_console_size_changes() {
    static int console_width = get_console_width();
    static int console_height = get_console_height();

    if (console_width != get_console_width() || console_height != get_console_height()) {
        console_width = get_console_width();
        console_height = get_console_height();
        return false;
    }
    else {
        return true;
    }
}

void move_cursor(const int x = 0, const int y = 0) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear(const int x, const int y, const int n = 1, const char symbol = ' ') {
    if (n < 0) return;
    if (x + n > get_console_width() || y > get_console_height()) {
        return;
    }
    string empty(n, symbol);
    move_cursor(x, y);
    cout << empty;
}

void clear_all() {
    for (unsigned int i{ 0 }; i < get_console_height(); i++) {
        clear(0, i, get_console_width());
    }
}

bool can_move_border(const int x, const int y) {
    if (x < 2 or y < 0) return false;   // Границы окна 
    if (x >= get_console_width() or y >= get_console_height()) return false;
    return true;
}


int get_color_code(const string& color) {
    if (color == "black") return 0;
    if (color == "blue") return 1;
    if (color == "green") return 2;
    if (color == "cyan") return 3;
    if (color == "red") return 4;
    if (color == "purple") return 5;
    if (color == "yellow") return 6;
    if (color == "white") return 7;
    return 7; // По умолчанию белый
}

void set_color(const int text_color_code, const int bg_color_code) {
    //  0 - Черный
    //  1 - Синий
    //  2 - Зеленый
    //  3 - Голубой
    //  4 - Красный
    //  5 - Пурпурный
    //  6 - Желтый
    //  7 - Белый(по умолчанию)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color_code | (bg_color_code << 4));
}

void set_color(const string& text_color, const string& bg_color) {
    int text_color_code = get_color_code(text_color);
    int bg_color_code = get_color_code(bg_color);

    set_color(text_color_code, bg_color_code);
}

void set_text_color(const int text_color_code) {
    set_color(text_color_code, 0);
}

void set_text_color(const std::string& text_color) {
    int text_color_code = get_color_code(text_color);

    set_color(text_color_code, 0);
}

void set_bg_color(const int bg_color_code) {
    set_color(7, bg_color_code);
}

void set_bg_color(const std::string& bg_color) {
    int bg_color_code = get_color_code(bg_color);

    set_color(7, bg_color_code);
}

void set_color() {
    set_color(7, 0);
}


void simulateF11() {
    INPUT input[2] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_F11;
    input[0].ki.dwFlags = 0;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_F11;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void disableMouseSelection() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS |
        (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}