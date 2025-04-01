#ifndef PLAYER_H
#define PLAYER_H

void player_print(const int player_x, const int player_y, const char cursor_type);
bool can_move_border(int x, int y);
void player_move(int& x, int& y, char& cursor_type);

#endif
