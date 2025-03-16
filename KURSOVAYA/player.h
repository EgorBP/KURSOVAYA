#ifndef PLAYER_H
#define PLAYER_H

void piy_clear(const int bullet_x, const int bullet_y, const char bullet_side);
bool is_piy_border(const int x, const int y, const char side);
void print_bullet(const int bullet_x, const int bullet_y, const char bullet_side);
bool is_arrow_on_enemy(const int bullet_x, const int bullet_y, const int enemy_x, const int enemy_y, const char bullet_type);

void player_print(const int player_x, const int player_y, const char cursor_type);
bool can_move_border(int x, int y);
void player_move(int& x, int& y, char& cursor_type);

#endif
