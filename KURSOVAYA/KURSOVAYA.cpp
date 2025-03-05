#include <iostream>
#include <windows.h>

using namespace std;


void set_color(int text_color, int bg_color = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color | (bg_color << 4));
}

int print_castle() {
    // От флага до флага 41 символ
    const string free_space(57, ' ');
    cout << free_space << "               /\\         /\\                    \n";
    cout << free_space << "             (^<>^)     (^<>^)                    \n";
    cout << free_space << "    __       /^/\\^\\     /^/\\^\\      __        \n";
    cout << free_space << " __:  |     / /  \\ \\   / /  \\ \\    |  :__     \n";
    cout << free_space << "|  :__|     |^^^^^^|   |^^^^^^|    |__:  |        \n";
    cout << free_space << "|__:  |     \\/\\/\\/\\/   \\/\\/\\/\\/    |  :__|\n";
    cout << free_space << "     / \\    |  __  |   |  __  |   / \\           \n";
    cout << free_space << "    /   \\   | |__| |   | |__| |  /   \\          \n";
    cout << free_space << "   /_____\\  |      |   |      | /_____\\         \n";
    cout << free_space << "   |     |==  ==  ==  ==  ==  ==|     |           \n";
    cout << free_space << "   |  _  | |__||__||__||__||__| |  _  |           \n";
    cout << free_space << "   | | | |                      | | | |           \n";
    cout << free_space << "   | |=| |   __           __    | |=| |           \n";
    cout << free_space << "   |     |  |  |    __   |  |   |     |           \n";
    cout << free_space << "   |     |  |==|   |::|  |==|   |     |           \n";
    cout << free_space << "   |     |         |::|         |     |           \n";
    cout << free_space << "   ~~~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~~~          \n";
    cout << free_space << "     ~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~            \n";
    cout << free_space << "        ~~~~~~~~~~~++++~~~~~~~~~~~                \n";
    cout << free_space << "                  ++++++                          \n";
    //cout << free_space << "                  ++++++                          \n";
    return 0;
}

void simulateF11() {
    INPUT input[2] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_F11;
    input[0].ki.dwFlags = 0;

    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VK_F11;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, input, sizeof(INPUT));
}

void move_cursor(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear(int x, int y) {
    move_cursor(x, y);
    cout << " ";
}

bool can_move(int x, int y) {
    if (x < 0 or y < 0) return false;   // Границы окна 
    if (x >= 156 or y >= 46) return false;
    if ((x > 56 && x < 99) && (y >= 2 && y <= 5)) return false;  // Флаг
    if ((x > 59 && x < 96) && (y >= 6 && y <= 15)) return false; // Стены
    if ((x > 68 && x < 87) && (y >= 0 && y <= 2)) return false;  // Верхушка
    return true;
}

int player_move(int& x, int& y, char& cursor_type) {
    clear(x, y);
    if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move(x - 2, y - 1)) { // Вверх и влево
        y -= 1;
        x -= 2;
    }
    else if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move(x + 2, y - 1)) { // Вверх и вправо
        y -= 1;
        x += 2;
    }
    else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move(x - 2, y + 1)) { // Вниз и влево
        y += 1;
        x -= 2;
    }
    else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move(x + 2, y + 1)) { // Вниз и вправо
        y += 1;
        x += 2;
    }
    else if (GetAsyncKeyState('W') & 0x8000 && can_move(x, y - 1)) { // Только вверх
        y -= 1;
    }
    else if (GetAsyncKeyState('S') & 0x8000 && can_move(x, y + 1)) { // Только вниз
        y += 1;
    }
    else if (GetAsyncKeyState('A') & 0x8000 && can_move(x - 2, y)) { // Только влево
        x -= 2;
    }
    else if (GetAsyncKeyState('D') & 0x8000 && can_move(x + 2, y)) { // Только вправо
        x += 2;
    }

    POINT p;
    HWND hwnd = GetConsoleWindow();
    GetCursorPos(&p);
    ScreenToClient(hwnd, &p);
    double x_pos = (double)p.x / 9.7;       // Переводим позицию мыши в координаты консоли ( +-1 )
    double y_pos = (double)p.y / 17.6;

    //std::cout << "Mouse X: " << x_pos << " Y: " << y_pos << std::endl;
    //cout << x << ' ' << y;

    // Так как расстояние между строками и столбцами не совпадает для корректного изменения 
    // требуется немного увеличить расстояние вертикальных курсоров
    if ((y - y_pos) * 1.9 >= abs(x - x_pos)) {
        cursor_type = '^';
    }
    else if ((y_pos - y) * 1.5 >= abs(x - x_pos)) {
        cursor_type = 'V';
    }
    else if ((x_pos - x) >= abs(y - y_pos)) {
        cursor_type = '>';
    }
    else if ((x - x_pos) >= abs(y - y_pos)) {
        cursor_type = '<';
    }

    move_cursor(x, y);
    cout << cursor_type;

    return 0;
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    hideCursor();
    Sleep(70);
    simulateF11();

    int player_x = 78;
    int player_y = 25;
    char player_type = 'V';

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        print_castle();
        set_color(2);
        player_move(player_x, player_y, player_type);
        move_cursor(0, 0);
        set_color(7);

        cout << R"(
       `.oo'    |    `oo.'
    ,.  (`-'    |    `-')  ,.
   '^\`-' )     |     ( `-'/^`
      c-L'-     |     -`_-)   
)";

        Sleep(80);
        move_cursor(0, 0);
        ShowCursor(TRUE);
    }

    //system("pause");
    return 0;
}