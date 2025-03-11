#ifndef PLAYER_H
#define PLAYER_H

void piy(int player_x, int player_y);
bool can_move_player(int x, int y);
void player_move(int& x, int& y, char& cursor_type);

#endif
