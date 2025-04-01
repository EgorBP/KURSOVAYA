#ifndef BOW_H
#define BOW_H

void arrow_clear(const int bullet_x, const int bullet_y, const char bullet_side);
bool is_arrow_border(const int x, const int y, const char side);
void print_arrow(const int bullet_x, const int bullet_y, const char bullet_side);
bool is_arrow_on_enemy(const int bullet_x, const int bullet_y, const int enemy_x, const int enemy_y, const char bullet_type);
void arrow_move(char** bullet_side, int** bullet_cord, Enemy** enemies, const int bullets, const int size);

#endif
