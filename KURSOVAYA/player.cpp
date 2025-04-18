#include <iostream>
#include <windows.h>
#include <string>
#include "services.h"
#include "player.h"

using namespace std;

void Player::player_clear() const {
	if (old_player_x != player_x || old_player_y != player_y) {
		clear(old_player_x, old_player_y);
	}
}

void Player::player_print(const Color color) const {
	move_cursor(player_x, player_y);
	set_text_color(color);
	cout << player_side;
	set_text_color(7);
}

void Player::player_move(const int points_x, const int points_y) {
	old_player_x = player_x;
	old_player_y = player_y;

	if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_border(player_x - points_x, player_y - points_y)) { // Вверх и влево
		player_y -= points_y;
		player_x -= points_x;
	}
	else if ((GetAsyncKeyState('W') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_border(player_x + points_x, player_y - points_y)) { // Вверх и вправо
		player_y -= points_y;
		player_x += points_x;
	}
	else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && can_move_border(player_x - points_x, player_y + points_y)) { // Вниз и влево
		player_y += points_y;
		player_x -= points_x;
	}
	else if ((GetAsyncKeyState('S') & 0x8000) && (GetAsyncKeyState('D') & 0x8000) && can_move_border(player_x + points_x, player_y + points_y)) { // Вниз и вправо
		player_y += points_y;
		player_x += points_x;
	}
	else if (GetAsyncKeyState('W') & 0x8000 && can_move_border(player_x, player_y - points_y)) { // Только вверх
		player_y -= points_y;
	}
	else if (GetAsyncKeyState('S') & 0x8000 && can_move_border(player_x, player_y + points_y)) { // Только вниз
		player_y += points_y;
	}
	else if (GetAsyncKeyState('A') & 0x8000 && can_move_border(player_x - points_x, player_y)) { // Только влево
		player_x -= points_x;
	}
	else if (GetAsyncKeyState('D') & 0x8000 && can_move_border(player_x + points_x, player_y)) { // Только вправо
		player_x += points_x;
	}

	POINT p;
	HWND hwnd = GetConsoleWindow();
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	double x_pos = static_cast<double>(p.x) / 9.7 * get_console_width() / 156;    // Переводим позицию мыши в координаты консоли ( +-1 )
	double y_pos = static_cast<double>(p.y) / 19 * get_console_height() / 46;		// (get_console_width() / 156) позволяет корректно отслеживать позицию при изменении масштаба

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

bool Player::is_player_on_door(const int door_x, const int door_y, const int door_width) const {
	if ((player_x >= door_x && player_x <= door_x + door_width - 1) && player_y == door_y) {
		return true;
	}
	else return false;
}
