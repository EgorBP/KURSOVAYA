#pragma once
#include <string>

using namespace std;

struct Dialogue {
	static string princess;
	static void process_princess();

	static string blacksmith;
	static void process_blacksmith();

	static void loop();
	static void print_dialogue_frame(const string& text, const string& heading);
};