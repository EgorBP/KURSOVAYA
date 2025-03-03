#include <iostream>
#include <windows.h>

using namespace std;


void set_color(int text_color, int bg_color = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color | (bg_color << 4));
}

int print_castle() {
    const string free_space(50, ' ');
    cout << free_space << "                     /\\         /\\\n";
    cout << free_space << "                   (^<>^)     (^<>^)\n";
    cout << free_space << "          __       /^/\\^\\     /^/\\^\\      __             \n";
    cout << free_space << "       __:  |     / /  \\ \\   / /  \\ \\    |  :__          \n";
    cout << free_space << "      |  :__|     |^^^^^^|   |^^^^^^|    |__:  |             \n";
    cout << free_space << "      |__:  |     \\/\\/\\/\\/   \\/\\/\\/\\/    |  :__|     \n";
    cout << free_space << "           / \\    |  __  |   |  __  |   / \\                \n";
    cout << free_space << "          /   \\   | |__| |   | |__| |  /   \\               \n";
    cout << free_space << "         /_____\\  |      |   |      | /_____\\              \n";
    cout << free_space << "         |     |==  ==  ==  ==  ==  ==|     |                \n";
    cout << free_space << "         |  _  | |__||__||__||__||__| |  _  |                \n";
    cout << free_space << "         | | | |                      | | | |                \n";
    cout << free_space << "         | |=| |   __           __    | |=| |                \n";
    cout << free_space << "         |     |  |  |    __   |  |   |     |                \n";
    cout << free_space << "         |     |  |==|   |::|  |==|   |     |                \n";
    cout << free_space << "         |     |         |::|         |     |                \n";
    cout << free_space << "         |_____|_________|::|_________|_____|~               \n";
    cout << free_space << "         ~~~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~~~               \n";
    cout << free_space << "           ~~~~~~~~~~~~~~++++~~~~~~~~~~~~~~~                 \n";
    cout << free_space << "              ~~~~~~~~~~~++++~~~~~~~~~~~                     \n";
    cout << free_space << "                        ++++++                               \n";
    cout << free_space << "                        ++++++                               \n";
    return 0;
}

void simulateF11() {
    INPUT input[2] = {};

    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VK_F11;
    input[0].ki.dwFlags = 0;
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
    if (x < 0 or y < 0) return false;
    if (x >= 156 or y >= 46) return false;
    //if (x > 56 and y > 17) return false;
    //if ()
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
    p.x /= 9;
    p.y /= 16;

    //std::cout << "Mouse X: " << p.x / 9 << " Y: " << p.y / 16 << std::endl;
    //cout << x << ' ' << y;

    // Так как расстояние между строками и столбцами не совпадает для корректного изменения 
    // требуется немного увеличить расстояние вертикальных курсоров
    if ((y - p.y) * 1.9 >= abs(x - p.x)) {
        cursor_type = '^';
    }
    else if ((p.y - y) * 1.5 >= abs(x - p.x)) {
        cursor_type = 'V';
    }
    else if ((p.x - x) >= abs(y - p.y)) {
        cursor_type = '>';
    }
    else if ((x - p.x) >= abs(y - p.y)) {
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

void showMouseCursor(bool show) {
    SystemParametersInfo(SPI_SETCURSORS, 0, nullptr, 0);
    if (!show) {
        ShowCursor(TRUE);
    }
}

void disableScroll() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;

    // Получаем текущий режим консоли
    GetConsoleMode(hConsole, &dwMode);

    // Отключаем режим прокрутки
    dwMode &= ~ENABLE_LINE_INPUT;
    dwMode &= ~ENABLE_ECHO_INPUT;

    SetConsoleMode(hConsole, dwMode);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    hideCursor();
    showMouseCursor(true);
    disableScroll();
    Sleep(100);
    simulateF11();
    //print_castle();

    int player_x = 2;
    int player_y = 2;
    char player_type = 'V';
    POINT p;

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        print_castle();
        set_color(2);
        player_move(player_x, player_y, player_type);
        set_color(7);

        Sleep(80);
        move_cursor(0, 0);
    }


    //system("pause");
    return 0;
}