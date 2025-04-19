#include "end.h";
#include "level.h"

bool End::is_end() {
	if (Level::get_current_level() > 10) return true;
	else return false;
}