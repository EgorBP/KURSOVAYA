#pragma once
#include <string>

struct Greeting {
    static const int size = 14;
    static const std::string first[size];
    static const std::string second[size];
    static const std::string third[2][6];
    static const std::string last[size];

    static const std::string end[size];

    static void greeting(int symobls_to_clear = 8);
    static void print_author_name();
    static void clear_author_name();
    static void print_end();
    static void beautiful_print(const std::string* item, int x_pos, int y_pos, int symobls_to_clear);
    static void game_name_print(int x, int y, int symobls_to_clear);
};
