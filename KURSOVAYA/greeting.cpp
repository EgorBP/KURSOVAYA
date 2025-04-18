#include <iostream>
#include <Windows.h>
#include "services.h"
#include "greeting.h"

using namespace std;

const string Greeting::first[size] = {
R"(                                 _____     _____   _____   _____   _____                          )",
R"(                                |  _  |   |  _  | |  ___| |  _  | |  _  |                         )",
R"(                                | | | |   | | | | | |___  | |_| | | | | |                         )",
R"(                               _| |_| |_  | | | | |  _  | |  ___| | | | |                         )",
R"(                              |  _____  | | |_| | | |_| | | |     | |_| |                         )",
R"(                              |_|     |_| |_____| |_____| |_|     |_____|                         )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(           _____   _____   __  _  __  _____    ____    _____   _____   _____   _______   _        )",
R"(          |  _  | |  _  |  \ \| |/ / |  _  |  |  _ \  |  _  | |  _  \ |  _  | |__   __| | |       )",
R"(          | | | | | | | |   \     /  | |_| |  | | | | | | | | | |_| / | |_| |    | |    | |___    )",
R"(          | | | | | | | |    |   |   |  _  |  | | | | | | | | |  _ |  |  _  |    | |    |  _  |   )",
R"(          | | | | | |_| |   /     \  | | | |  | | | | | |_| | | |_| \ | | | |    | |    | |_| |   )",
R"(          |_| |_| |_____|  /_/|_|\_\ |_| |_|  /_/ |_| |_____| |_____/ |_| |_|    |_|    |_____|   )"
};

const string Greeting::second[size] = {
R"(                                                 _____                                            )",
R"(                                                |  _  \                                           )",
R"(                                                | |_| /                                           )",
R"(                                                |  _ |                                            )",
R"(                                                | |_| \                                           )",
R"(                                                |_____/                                           )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                    _     _   _____   _____  __    __                             )",
R"(                                   | |   / | | ____| |  _  | \ \  / /                             )",
R"(                                   | |  // | | |     | |_| |  \ \/ /                              )",
R"(                                   | | //| | | |     |  ___|   \  /                               )",
R"(                                   | |// | | | |     | |       / /                                )",
R"(                                   |_ /  |_| |_|     |_|      /_/                                 )",
};

const string Greeting::third[2][6] = {
{
R"(                              _____   _____   _____   _____   _______   _     _                   )",
R"(                             |  ___| |  _  | |  _  | |  ___| |__   __| | |   / |                  )",
R"(                             | |     | | | | | |_| | | |        | |    | |  // |                  )",
R"(                             | |     | | | | |  _  | | |        | |    | | //| |                  )",
R"(                             | |___  | | | | | | | | | |___     | |    | |// | |                  )",
R"(                             |_____| |_| |_| |_| |_| |_____|    |_|    |_ /  |_|                  )",
},
{
R"(                  _____   _____   _     _   _   _   _   _    _____   _____   _____  __    __      )",
R"(                 |  _  | |  _  | | |   / | | | | | | | | |  |  ___| |  ___| |  ___| \ \  / /      )",
R"(                 | | | | | |_| | | |  // | | |_| | | | | |  | |___  | |     | |      \ \/ /       )",
R"(                 | | | | |  ___| | | //| | |  _  | | |_| |  |  ___| | |     | |       \  /        )",
R"(                 | | | | | |     | |// | | | | | | |____ |  | |___  | |___  | |___    / /         )",
R"(                 |_| |_| |_|     |_ /  |_| |_| |_|      \_\ |_____| |_____| |_____|  /_/          )",
}
};

const string Greeting::last[size] = {
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
R"(                                                                                                  )",
};

void Greeting::greeting(int symobls_to_clear) {
    const int x = 25;
    const int y = 15;

    print_author_name();

    beautiful_print(first, x, y, symobls_to_clear);
    Sleep(1000);
    beautiful_print(second, x, y, symobls_to_clear);
    Sleep(1000);
    game_name_print(x, y, symobls_to_clear);
    Sleep(1000);
    beautiful_print(last, x, y, symobls_to_clear);
    
    clear_author_name();
}

void Greeting::print_author_name() {
    move_cursor(132, 45);
    cout << "Made with";
    set_text_color(Color::Purple);
    cout << " love ";
    set_color();
    cout << "by ";
    set_text_color(Color::Green);
    cout << "EgorBP";
    set_color();
}

void Greeting::clear_author_name() {
    clear(132, 45, 24);
}

void Greeting::beautiful_print(const string* item, const int x_pos, const int y_pos, int symobls_to_clear) {
    const int width = item[0].size();
    for (int i{ 0 }; i < width; i++) {
        for (int height{ 0 }; height < size; height++) {
            move_cursor(x_pos + i, y_pos + height);
            cout << item[height][i];
            clear(x_pos + i + 1, y_pos + height, symobls_to_clear);
        }
        Sleep(1);
    }
}

void Greeting::game_name_print(int x_pos, int y_pos, int symobls_to_clear) {
    const int width = third[0][0].size();
    for (int i{ 0 }; i < width; i++) {
        for (int height{ 0 }; height < 6; height++) {
            move_cursor(x_pos + i, y_pos + height);
            set_text_color(Color::Cyan);
            cout << third[0][height][i];
            clear(x_pos + i + 1, y_pos + height, symobls_to_clear);

            move_cursor(x_pos + i, y_pos + height + 8);
            set_text_color(Color::Yellow);
            cout << third[1][height][i];
            clear(x_pos + i + 1, y_pos + height + 8, symobls_to_clear);

            set_color();
        }
        Sleep(1);
    }
}
