#pragma once
#include <string>
#include "level.h"

enum DialogueObject {
	Princess,
	Blacksmith,
};

enum BlacksmithItems {
	BowDamageUpgrade,
	BombBuy,
};

struct BlacksmithClass {
	BlacksmithItems current_item;

	static const int items_count = 2;

	static const std::string filename;

	void print_pointer() const;
	void clear_pointer() const;
	static void print_all_items();
	static void print_money();
	static int get_money_from_item(BlacksmithItems item);
	static void print_help();

private:
	static void print_body(const int y_pos, const std::string& text, const int price, int (*get_data)());
};

struct Dialogue {
	static bool exit;
	static DialogueObject current_object;

	static const std::string filename;

	static std::string princess_art;
	static const std::string princess_dialogues[Level::max_level + 1][6];
	static void process_princess();

	static std::string blacksmith_art;
	static void process_blacksmith(BlacksmithClass& blacksmith);

	static void loop();
	static void print_dialogue_frame(const std::string& text, const std::string& heading);

	static int get_current_money();
	static void money_up(const int points = 1);
	static void set_new_money(const int new_money);

	static void read_princess();
	static void read_blacksmith();
};