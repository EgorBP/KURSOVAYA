#include <iostream>
#include <windows.h>
#include "services.h"
#include "player.h"

using namespace std;

void Player::player_print() const {
	move_cursor(player_x, player_y);
	set_color(2);
	cout << player_side;
	set_color(7);
}

void Player::player_move() {
	clear(player_x, player_y);
	if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_border(player_x - 2, player_y - 1)) { // Вверх и влево
		player_y -= 1;
		player_x -= 2;
	}
	else if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_border(player_x + 2, player_y - 1)) { // Вверх и вправо
		player_y -= 1;
		player_x += 2;
	}
	else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_border(player_x - 2, player_y + 1)) { // Вниз и влево
		player_y += 1;
		player_x -= 2;
	}
	else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_border(player_x + 2, player_y + 1)) { // Вниз и вправо
		player_y += 1;
		player_x += 2;
	}
	else if (GetAsyncKeyState('W') & 0x8000 && can_move_border(player_x, player_y - 1)) { // Только вверх
		player_y -= 1;
	}
	else if (GetAsyncKeyState('S') & 0x8000 && can_move_border(player_x, player_y + 1)) { // Только вниз
		player_y += 1;
	}
	else if (GetAsyncKeyState('A') & 0x8000 && can_move_border(player_x - 2, player_y)) { // Только влево
		player_x -= 2;
	}
	else if (GetAsyncKeyState('D') & 0x8000 && can_move_border(player_x + 2, player_y)) { // Только вправо
		player_x += 2;
	}

	POINT p;
	HWND hwnd = GetConsoleWindow();
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	double x_pos = (double)p.x / 9.7;       // Переводим позицию мыши в координаты консоли ( +-1 )
	double y_pos = (double)p.y / 17.6;

	//std::cout << "Mouse X: " << x_pos << " Y: " << y_pos << std::endl;
	//cout << player_x << ' ' << player_y;

	// Так как расстояние между строками и столбцами не совпадает для корректного изменения 
	// требуется немного увеличить расстояние вертикальных курсоров
	if ((player_y - y_pos) * 1.9 >= abs(player_x - x_pos)) {
		player_side = '^';
	}
	else if ((y_pos - player_y) * 1.5 >= abs(player_x - x_pos)) {
		player_side = 'V';
	}
	else if ((x_pos - player_x) >= abs(player_y - y_pos)) {
		player_side = '>';
	}
	else if ((player_x - x_pos) >= abs(player_y - y_pos)) {
		player_side = '<';
	}
}
