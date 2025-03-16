#ifndef SERVICES_H
#define SERVICES_H

void move_cursor(const short x, const short y);
void clear(int x, int y, int n = 1);
void set_color(int text_color, int bg_color = 0);
bool can_move_border(const int x, const int y);

void end_game();

void simulateF11();
void hideCursor();
void disableMouseSelection();

#endif
