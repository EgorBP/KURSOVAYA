#ifndef SERVICES_H
#define SERVICES_H

#include <string>

enum Color {
//  0 - Черный
	Black,
//  1 - Синий
	Blue,
//  2 - Зеленый
	Green,
//  3 - Голубой
	Cyan,
//  4 - Красный
	Red,
//  5 - Пурпурный
	Purple,
//  6 - Желтый
	Yellow,
//  7 - Белый(по умолчанию)
	White,
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
bool check_esc_button();
bool check_enter_button();

void set_color(const int text_color_code, const int bg_color_code);
void set_color(const Color text_color, const Color bg_color);
void set_text_color(const int text_color_code);
void set_text_color(const Color text_color);
void set_bg_color(const int bg_color_code);
void set_bg_color(const Color bg_color);
void set_color();

void prepare_console();
void simulateF11();
void hideCursor();
void disableMouseSelection();

#endif
