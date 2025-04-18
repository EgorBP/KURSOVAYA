#ifndef SERVICES_H
#define SERVICES_H

#include <string>

enum Color {
//  0 - Черный
	black,
//  1 - Синий
	blue,
//  2 - Зеленый
	green,
//  3 - Голубой
	cyan,
//  4 - Красный
	red,
//  5 - Пурпурный
	purple,
//  6 - Желтый
	yellow,
//  7 - Белый(по умолчанию)
	white,
};

int get_console_width();
int get_console_height();
int get_cursor_x();
int get_cursor_y();
bool check_console_size_changes();
int get_first_line_width(std::string text);
void move_cursor(const int x = 0, const int y = 0);
void clear(const int x, const int y, const int n = 1, const char symbol = ' ');
void clear_all();
void beautiful_clear_all(int sleep_time = 0, char symbol = ' ');
bool can_move_border(const int x, const int y);
bool check_right_left_buttons();

int get_color_code(const std::string& color);
void set_color(const int text_color_code, const int bg_color_code);
void set_color(const std::string& text_color, const std::string& bg_color);
void set_text_color(const int text_color_code);
void set_text_color(const std::string& text_color);
void set_bg_color(const int bg_color_code);
void set_bg_color(const std::string& bg_color);
void set_color();

void prepare_console();
void simulateF11();
void hideCursor();
void disableMouseSelection();

#endif
