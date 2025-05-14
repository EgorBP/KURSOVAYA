#include "end.h";
#include "level.h"
#include "bow.h"

bool End::is_end() {
	if (Level::get_current_level() > 10) return true;
	else return false;
}

void End::process_end() {
	Level::set_new_level(0);
	Arrow::set_new_level(1);
}
