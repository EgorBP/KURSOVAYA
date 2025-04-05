#ifndef SERVICES_H
#define SERVICES_H

#include <string>

void move_cursor(const int x = 0, const int y = 0);
void clear_all();
void clear(const int x, const int y, const int n = 1, const char symbol = ' ');
int get_color_code(const std::string& color);
void set_color(const std::string& text_color, const std::string& bg_color = "black");
void set_color(const int text_color, const int bg_color);
void set_color(const int text_color);
bool can_move_border(const int x, const int y);

void end_game();

void simulateF11();
void hideCursor();
void disableMouseSelection();

#endif
