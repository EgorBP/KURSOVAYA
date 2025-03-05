#ifndef SERVICES_H
#define SERVICES_H

void move_cursor(short x, short y);
void clear(int x, int y);
void set_color(int text_color, int bg_color = 0);
void simulateF11();
void hideCursor();

#endif
