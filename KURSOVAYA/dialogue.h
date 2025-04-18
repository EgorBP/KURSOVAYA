#pragma once
#include <string>
#include "level.h"

enum DialogueObject {
	princess,
	blacksmith,
};

struct Dialogue {
	static DialogueObject current_object;

	static std::string princess;
	static const std::string princess_dialogues[Level::max_level][6];
	static void process_princess();

	static std::string blacksmith;
	static void process_blacksmith();

	static void loop();
	static void print_dialogue_frame(const std::string& text, const std::string& heading);

	static int get_current_money();
	static void money_up(const int points = 1);
	static void set_new_money(const int new_money);
};