#ifndef SERVICES_H
#define SERVICES_H

#include <string>

int get_console_width();
int get_console_height();
bool check_console_size_changes();
void move_cursor(const int x = 0, const int y = 0);
void clear_all();
void clear(const int x, const int y, const int n = 1, const char symbol = ' ');
bool can_move_border(const int x, const int y);

int get_color_code(const std::string& color);
void set_color(const int text_color_code, const int bg_color_code);
void set_color(const std::string& text_color, const std::string& bg_color);
void set_text_color(const int text_color_code);
void set_text_color(const std::string& text_color);
void set_bg_color(const int bg_color_code);
void set_bg_color(const std::string& bg_color);
void set_color();


void simulateF11();
void hideCursor();
void disableMouseSelection();

#endif
