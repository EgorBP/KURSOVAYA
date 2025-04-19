#include <iostream>
#include <Windows.h>
#include <string>
#include "services.h"
#include "player.h"
#include "castle.h"

using namespace std;

const string Castle::castle[] = {
"                        /\\         /\\  ",
"                      (^<>^)     (^<>^) ",
"             __       /^/\\^\\     /^/\\^\\      __",
"          __:  |     / /  \\ \\   / /  \\ \\    |  :__",
"         |  :__|     |^^^^^^|   |^^^^^^|    |__:  |",
"         |__:  |     \\/\\/\\/\\/   \\/\\/\\/\\/    |  :__|",
"              / \\    |  __  |   |  __  |   / \\  ",
"             /   \\   | |__| |   | |__| |  /   \\ ",
"            /_____\\  |      |   |      | /_____\\" ,
"            |     |==  ==  ==  ==  ==  ==|     |",
"            |  _  | |__||__||__||__||__| |  _  |",
"            | | | |                      | | | |  ~",
" ~      ~~~~| |=| |   __            __   | |=| |~~~~~   ~              ",
"     ~~~~~~~|     |  |  |    __    |  |  |     |~~~~~~~~    ~          ",
"~   ~~~~~   |     |  |==|   |::|   |==|  |     |   ~~~~~~~        ~    ",
"   ~~~~~    |     |         |::|         |     |~    ~~~~~~            ",
"   ~~~~     |_____|_________|::|_________|_____|~~    ~~~~~~   ~       ",
"   ~~~~     ~~~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~~~      ~~~~~           ",
"    ~~~~      ~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~       ~~~~~~           ",
"      ~~~~       ~~~~~~~~~~~++++~~~~~~~~~~~         ~~~~~~~      ~",
"~        ~~~~~             ++++++                 ~~~~~",
"            ~~~ ~~  ~  ~ ~ ++++ +  ~~   ~~   ~~~ ~~~~",
"       ~        ~  ~    ~  ++++++~ ~  ~ ~  ~~               ~",
"            ~      ~ ~   ~ + ++++~     ~~    ~       ~",
"               ~    ~  ~   ++++++ ~~   ~ ~",
"   ~      ~        ~~ ~    ++++++  ~~   ~    ~",
"                 ~      ~ ~+++ ++   ~     ~       ~",
"          ~        ~     ~ ++++++~    ~  ~ ~",
};

void Castle::print_castle(const Player& player) {
    const int player_x = player.player_x;
    const int player_y = player.player_y;

    size_t castle_size = sizeof(castle) / sizeof(castle[0]);

    // Размеры консоли: x = 156, y = 45
    // Размеры замка: 24 строки, 61 символа самая длинная строка
    for (int i{ 0 }; i < get_console_height() - 1; i++) {
        if (i > empty_spaces && i < empty_spaces + castle_size + 1) {
            clear(0, i, free_left_space + 1);
            if (i - empty_spaces > 11) {
                int x_index = free_left_space;
                bool is_water = true;
                bool is_first_water = true;
                for (char symbol : castle[i - empty_spaces - 1]) {
                    x_index++;
                    if (!(i == player_y && x_index == player_x)) {
                        if (symbol == '~' && is_water) {
                            set_text_color(Color::Cyan);
                            is_first_water = false;
                        }
                        else if (symbol == '~') {
                            set_text_color(Color::Green);
                        }
                        if (symbol == '+') {
                            set_text_color(Color::Yellow);
                        }
                        if (symbol == ':') {
                            set_text_color(Color::Red);
                        }
                        if (!is_first_water && i - empty_spaces < 21 && i - empty_spaces > 15 && x_index - free_left_space < 61 &&
                            (symbol == ' ' || symbol == '|') && castle[i - empty_spaces - 1][x_index - free_left_space] == '~') {
                            is_water = !is_water;
                        }
                        cout << symbol;
                        set_color();
                    }
                    else {
                        move_cursor(x_index + 1, i);
                    }
                }
                cout << endl;
                set_color();
            }
            else {
                cout << castle[i - empty_spaces - 1] << endl;
            }
        }
        else {
            //clear(0, i, 156);
            cout << endl;
        }
    }
}

int Castle::find_door_index() {
    for (int i{ 0 }; i < castle[16].size(); i++) {
        if (castle[16][i] == ':') {
            return i + free_left_space + 1;
        }
    }
    return -1;
}

bool Castle::can_move_castle(int player_x, int player_y) {
    if (!can_move_border(player_x, player_y)) return false;

    size_t castle_size = sizeof(castle) / sizeof(castle[0]) - 1;

    if ((player_y == empty_spaces + 18) &&      // Трава 1
        ((player_x < free_left_space + 13) || (player_x > free_left_space + 49)))
        return false;
    else if ((player_y == empty_spaces + 19) && // Трава 2
        ((player_x < free_left_space + 15) || (player_x > free_left_space + 47)))
        return false;
    else if ((player_y == empty_spaces + 20) && // Трава 3
        ((player_x < free_left_space + 18) || (player_x > free_left_space + 43)))
        return false;
    else if (player_y < empty_spaces + 18 &&    // Двери
        ((player_x < castle[16].find_first_of(':') + free_left_space + 1) || (player_x > castle[16].find_last_of(':') + free_left_space + 1)))
        return false;
    else if (((player_y < castle_size + empty_spaces + 2) && (player_y > empty_spaces + 20)) &&   // Вода и мост
        ((player_x < castle[castle_size].find_first_of('+') + free_left_space + 1) || (player_x > castle[castle_size].find_last_of('+') + free_left_space + 1)))
        return false;
}