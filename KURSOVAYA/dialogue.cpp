#include <iostream>
#include <string>
#include <fstream>
#include "Windows.h"
#include "dialogue.h"
#include "level.h"
#include "services.h"
#include "bow.h"
#include "bomb.h"

using namespace std;

DialogueObject Dialogue::current_object = DialogueObject::Princess;
bool Dialogue::exit = false;

const string BlacksmithClass::filename = "Data\\money.txt";
const string Dialogue::filename = "Data\\arts.txt";


void Dialogue::loop() {
	clear_all();
	BlacksmithClass blacksmith{ BlacksmithItems::BowDamageUpgrade };
	exit = false;

	while (!exit) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			beautiful_clear_all();
			// ���� ����� �������� �� ����������� ����� �� ��������� �����
			Sleep(100);
			break;
		}

		// ����� ���� ��� ����� �� �������������� ������
		if (!check_console_size_changes()) {
			clear_all();
		}

		if (current_object == DialogueObject::Princess) {
			if (check_right_left_buttons()) {
				current_object = DialogueObject::Blacksmith;
				beautiful_clear_all();
			}
			else {
				process_princess();
			}
		}
		else if (current_object == DialogueObject::Blacksmith) {
			if (check_right_left_buttons()) {
				current_object = DialogueObject::Princess;
				beautiful_clear_all();
			}
			else {
				process_blacksmith(blacksmith);
			}
		}
		Sleep(15);
	}
}

void Dialogue::print_dialogue_frame(const string& text, const string& heading) {
	set_text_color(Color::Green);
	move_cursor((get_console_width() - get_first_line_width(text) - heading.length()) / 2 + get_first_line_width(text) + 2);
	cout << heading;

	set_text_color(Color::Purple);
	clear(get_first_line_width(text) + 1, 1, get_console_width() - get_first_line_width(text) - 1, '_');
	clear(get_first_line_width(text) + 2, get_console_height() - 1, get_console_width() - get_first_line_width(text) - 3, '_');

	for (int i{ 2 }; i < get_console_height(); i++) {
		move_cursor(get_first_line_width(text) + 1, i);
		cout << '|';
		move_cursor(get_console_width() - 1, i);
		cout << '|';
	}

	set_color();
}

void Dialogue::process_princess() {
	print_dialogue_frame(princess_art, "���������");
	move_cursor();
	cout << princess_art;

	string word = "";
	bool run = true;
	int level_index = Level::get_current_level() - 1;

	if (level_index < 0 || level_index >= Level::max_level) {
		return;
	}

	for (int i{ 0 }, new_strings_cout{ 0 }; i < 6 && run; i++) {
		const std::string& line = princess_dialogues[level_index][i];

		if (line.empty()) {
			continue;
		}

		cout << word;
		word = "";
		if (i != 0) Sleep(1000);
		move_cursor(get_first_line_width(princess_art) + 4, 3 + i * 2 + new_strings_cout);

		for (char symbol : line) {
			if (check_esc_button()) {
				beautiful_clear_all();
				exit = true;
				run = false;
				break;
			}
			if (check_right_left_buttons()) {
				current_object = DialogueObject::Blacksmith;
				beautiful_clear_all();
				run = false;
				break;
			}
			word += symbol;
			if (get_cursor_x() + word.length() >= get_console_width() - 1 || symbol == '\n') {
				new_strings_cout++;
				move_cursor(get_first_line_width(princess_art) + 4 + 1, 3 + i * 2 + new_strings_cout);
			}
			if (symbol == ' ' || symbol == '\0') {
				Sleep(100);
				cout << word;
				word = "";
			}
		}
	}
	Sleep(50);
	cout << word;
	word = "";
}

void Dialogue::process_blacksmith(BlacksmithClass& blacksmith) {
	print_dialogue_frame(blacksmith_art, "������");
	move_cursor();
	cout << blacksmith_art;

	BlacksmithClass::print_money();
	BlacksmithClass::print_all_items();
	BlacksmithClass::print_help();

	if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) {
		if (blacksmith.current_item > 0) {
			blacksmith.clear_pointer();
			blacksmith.current_item = static_cast<BlacksmithItems>(blacksmith.current_item - 1);
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (blacksmith.current_item < BlacksmithClass::items_count - 1) {
			blacksmith.clear_pointer();
			blacksmith.current_item = static_cast<BlacksmithItems>(blacksmith.current_item + 1);
		}
	}

	move_cursor(get_console_width() - 6, get_console_height() - 3);
	cout << blacksmith.current_item;
	blacksmith.print_pointer();

	if (blacksmith.current_item == BlacksmithItems::BowDamageUpgrade) {
		if (check_enter_button() && Dialogue::get_current_money() >= BlacksmithClass::get_money_from_item(blacksmith.current_item)) {
			Dialogue::money_up(-BlacksmithClass::get_money_from_item(blacksmith.current_item));
			Arrow::level_up();
			Sleep(100);
		}
	}
	else if (blacksmith.current_item == BlacksmithItems::BombBuy) {
		if (check_enter_button() && Dialogue::get_current_money() >= BlacksmithClass::get_money_from_item(blacksmith.current_item)) {
			Dialogue::money_up(-BlacksmithClass::get_money_from_item(blacksmith.current_item));
			Bomb::count_up();
			Sleep(100);
		}
	}
}

void BlacksmithClass::print_pointer() const {
	set_text_color(Color::Green);
	move_cursor(get_first_line_width(Dialogue::blacksmith_art) + 6, 5 + current_item * 2);
	cout << "->";
	set_color();
}

void BlacksmithClass::clear_pointer() const {
	clear(get_first_line_width(Dialogue::blacksmith_art) + 6, 5 + current_item * 2, 2);
}

void BlacksmithClass::print_money() {
	set_text_color(Color::Yellow);
	move_cursor(get_console_width() - 6, 3);
	cout << Dialogue::get_current_money() << "  ";
	move_cursor();
}

void BlacksmithClass::print_all_items() {
	print_body(0, "���������� ����� ������", BlacksmithClass::get_money_from_item(BlacksmithItems::BowDamageUpgrade), Arrow::get_bow_level);
	print_body(1, "����� �����", BlacksmithClass::get_money_from_item(BlacksmithItems::BombBuy), Bomb::get_current_count);
}

void BlacksmithClass::print_body(const int y_pos, const string& text, const int price, int (*get_data)()) {
	move_cursor(get_first_line_width(Dialogue::blacksmith_art) + 8, 5 + y_pos * 2);
	set_color();
	cout << text << " (";
	set_text_color(Color::Red);
	cout << get_data();
	set_color();
	cout << "->";
	set_text_color(Color::Green);
	cout << get_data() + 1;
	set_color();
	cout << ')';

	move_cursor(get_console_width() - 12, 5 + y_pos * 2);
	if (Dialogue::get_current_money() < price) {
		set_text_color(Color::Red);
	}
	else {
		set_text_color(Color::Green);
	}
	cout << price;
	set_color();

}

int BlacksmithClass::get_money_from_item(BlacksmithItems item) {
	switch (item) {
	case BlacksmithItems::BowDamageUpgrade:
		return 50;
	case BlacksmithItems::BombBuy:
		return 15;
	default:
		return -1;
	}
}

void BlacksmithClass::print_help() {
	move_cursor(get_first_line_width(Dialogue::blacksmith_art) + 6, get_console_height() - 5);
	cout << "'W' - �����";
	move_cursor(get_first_line_width(Dialogue::blacksmith_art) + 6, get_console_height() - 4);
	cout << "'S' - ����";
	move_cursor(get_first_line_width(Dialogue::blacksmith_art) + 6, get_console_height() - 3);
	cout << "'Enter' - ������";

}

int Dialogue::get_current_money() {
	int level = 0;
	fstream file(BlacksmithClass::filename, ios::in);
	if (file.is_open()) {
		file >> level;
		file.close();
	}
	else {
		set_new_money(level);
	}
	file.close();
	return level;
}

void Dialogue::money_up(const int points) {
	int current_level = get_current_money();
	fstream file(BlacksmithClass::filename, ios::out | ios::trunc);
	if (file.is_open()) {
		file << current_level + points;
		file.close();
	}
}

void Dialogue::set_new_money(const int new_level) {
	fstream file(BlacksmithClass::filename, ios::out | ios::trunc);
	if (file.is_open()) {
		file << new_level;
		file.close();
	}
}

void Dialogue::read_princess() {
	ifstream file(Dialogue::filename);

	if (!file) {
		cout << "������ �������� �����.";
		return;
	}

	string s = "";
	int arts_count = 1;
	for (int i{ 0 }; getline(file, s) ; i++) {
		if (s.empty()) {
			i = 0;
			arts_count++;
			if (arts_count == 3) break;
		}
		else if (arts_count == 2) {
			Dialogue::princess_art += s + '\n';
		}
	}
	Dialogue::princess_art.pop_back();
}

void Dialogue::read_blacksmith() {
	ifstream file(Dialogue::filename);

	if (!file) {
		cout << "������ �������� �����.";
		return;
	}

	string s = "";
	int arts_count = 1;
	for (int i{ 0 }; getline(file, s); i++) {
		if (s.empty()) {
			i = 0;
			arts_count++;
			if (arts_count == 4) break;
		}
		else if (arts_count == 3) {
			Dialogue::blacksmith_art += s + '\n';
		}
	}
	Dialogue::blacksmith_art.pop_back();
}



const string Dialogue::princess_dialogues[Level::max_level + 1][6] = {
	{
		"���������: ��� ��? ��� ���-�� ���� ������ ����� ��� ��� �����?",
		"������: � � ������. � ������, ����� �������� �������. � ����� ������ ���������� ����.",
		"���������: �� ������ ���� ����? �� �� �� ������ ������ �� ���� �����.",
		"������: � �� �����. � � ����� ���. � �� ������ ����.",
		"���������: �� � ������, ��� ���� ������ ����� �����. ��� ������ ������ ������?",
		"������: � ������ ��, ����� ������� ���� ���������."
	},
	{
		"���������: �� ������������� �� ������� ����� �����?",
		"������: ������, � ����� � ������ � �� ��������.",
		"���������: �� �����, �� ����� �� �� ��� ������. ��� ����� �������� ������, ������� ��������� ���� � ���.",
		"������: � ������, ��� ����� ����� ������ ���������� ����. �� �� ������ ���������� �����.",
		"���������: �� �� ���������� � �� ���� �������� ���� �����. ߅ � ����� ��� ������."
	},
	{
		"������: �� ��������, ��� ����� ������ ����. ��� ������ ��� ������? ������ �� �� ������ ������ ����?",
		"���������: ��� ���������. � ������� �����, ����� �� ������ ����, � ������ ��� ����� ������ ���� �����. � �� ���� ����, � ��������.",
		"������: �� �� ���� �� �������� � ����, �����? �� �� �����, ��� ���������.",
		"���������: ��������. �� ������ � �����, � ���� ����� ���� ���� ������. � �� ���� �������� ��, ��� ���������.",
		"������: � �������� ����, ��� ������ ��������� � ���� ����������. �� ����� �����.",
		"���������: ��� ���������? �� ������, ��� ����� �������� ������?"
	},
	{
		"������: ������ ���, ����� � ��������� ���� �������, � ��������, ��� ��������� ����������. ��� ��� ���� ��� ����?",
		"���������: ��� ���� ����. �� �� ������ ���������� � ����������, �� ���������� �� ����� � ���� ������. ��� ������� ���������.",
		"������: ���� � ����� ���������� ���� ������, �� ������� ����?",
		"���������: ��� �� ��� ������. ������ ����� �� �������� ���-�� ������� � ������ � ��� ������.",
		"������: ����� � ���� ��������� ������. �� ��� �� ���.",
		"���������: �� ������ � ��, ��� � ���� ���� ���������? ��� ������ ������."
	},
	{
		"���������: �� ����� ��������. � ������� ������, ��� �� �� ������ ������ �� ���� ���������.",
		"������: � ������, ����� ���������� ����. �� � �� ���� ������, ��� ������ ��� ��� ���������� �� ����� � ����� ��������.",
		"���������: �� ���� �� ������ ������. ��... �� �����, ��� ������.",
		"������: � ��� ���, ��� �������� �� �����. �� ������ � �������� �� ����. �� �� ������ ���� � ���� �����.",
		"���������: � ���� ������ � ���� ����. �� �� �� �������, ��� ����� �������� ��� �����.",
		"������: �� ������ ��������. ��� ��� ����."
	},
	{
		"���������: �� ����������� ��������� �����, �������� �� ��. � ��������, ��� �������� ���������. �� ������������� ������ ���������� ����.",
		"������: � ������ ����� ������ � ��������, ��� � ����������� � ����. �� �� ������ ������ �����.",
		"���������: � �� ����, ����� �� � ���������. ��� ����� ����� ���� �����. � ������� � ���.",
		"������: �� ��� � ��� �� ����� � �� ���������. ��� � ��� �������. � ���� ������.",
		"���������: �� � ��� ������������ ����. � �� ���� �������� � ���� �������."
	},
	{
		"������: � ����� ��������. ����� ������� ���� �������. �� ��� �����, ���� � �������� ����?",
		"���������: �� ������ �������� �������. �� �� ������, ����� ��������� ���������!",
		"������: � ������� ���. �� � �� ������ ���� ������ � ����, ��� ������������ �� ��� ������.",
		"���������: � ������. ���� �� �������� ��, ��� ����� ��������, � ���� ��������.",
		"������: � �� ����� ���� ������. ������� �������. �� ������ �� ������ ����.",
		"���������: � �� �����, ����� � ��������� ��� � �����������, ��� �� ����."
	},
	{
		"������: �� �������� � ���, ��� ������� �����, � ����� ������� ���� ������� �� �����...",
		"���������: ��. ������ ���� ����� �������� ���� �����. � ��� �������� ��� �... ����.",
		"������: � �� �����. � ������ ���� ���� � �������� �� ���� ����� �� ���� ��������.",
		"���������: � ���� � ����. � ���� � ��, ��� �� ������� ��� �������. ����� � �� ������ �� ����������."
	},
	{
		"���������: ������ ���� ��� ���������� ���� � �������. � ��������, ��� ����� �������.",
		"������: �������� �������. � ����, ��� ����� ������ ���� ����.",
		"���������: �� � ���� ������ � ����� ����. � �� ����, ��� ���� ��� ���� ����.",
		"������: �� ������� �����. ��� ���������, ��� ����. ������ �����.",
		"���������: ���� �� �� ��, � �� ����� ������, ������ ��� � ���������.",
		"������: ����� ������� �� ��� �������. ��� ������� ����� �����."
	},
	{
		"������: � ����� �� �������� ������. ��� �������� ������ �� ������ ��� �������. �� ��� �� �� ������� ����, ��� ����� �����?",
		"���������: � �� �����. � ������ ���� ���� ���������. �� ������ ��� ���� ������, ��� ����� ������.",
		"������: ���� �� ����� ����� �������. �� ������ �� ����.",
		"���������: � ������� �� ���. �� � ��, ��� � ���� ����."
	},
	{
		"������: �� ���������. ���� �������. ��������� ���������. �� ��������.",
		"���������: �� ������ �����������. �� ��������� ����.",
		"������: ������ �� �� ����. � ������� ������ �� ������.",
		"���������: �� ������� ���, ��� ������ ��������� ���� � �� � �����, � � ����. �������, ������.",
		"���������: �� �� ������ ��������� ����. �� ��������� ��� �����."
	}
};

string Dialogue::princess_art;

string Dialogue::blacksmith_art;