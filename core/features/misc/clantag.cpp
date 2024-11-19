#include <pch.h>
#include "../features.hpp"

std::vector<std::string> clantag_frames{ xorstr("|"), xorstr("U"), xorstr("U|"), xorstr("Uw"), xorstr("Uw|"), xorstr("Uwu"), xorstr("Uwu|"), xorstr("Uwut"), xorstr("Uwut|"), xorstr("Uwuti"), xorstr("Uwuti|"), xorstr("Uwutil"), xorstr("Uwutil|"), xorstr("Uwutils"), xorstr("Uwutil"), xorstr("Uwutil|"), xorstr("Uwutil"), xorstr("Uwuti|"), xorstr("Uwuti"), xorstr("Uwut|"), xorstr("Uwut"), xorstr("Uwu|"), xorstr("Uwu"), xorstr("Uw|"), xorstr("Uw"), xorstr("U|"), xorstr("U"), xorstr("|") };
int last_frame;
bool reset = false;

void features::misc::clantag() {
	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	if (var::misc::clantag) {
		// This will move 1 frame every second
		float tps = 0.4f / interfaces::globals->interval_per_tick;
		int current_frame = static_cast<int>(floor(interfaces::globals->tick_count / tps)) % clantag_frames.size();

		// Check if last frame was the current frame
		if (last_frame != current_frame) {
			util::set_clantag(clantag_frames[current_frame].c_str());
			last_frame = current_frame;
		}

		reset = true;
	}
	else if (reset) {
		// Reset clantag
		util::set_clantag(xorstr(""));
		reset = false;
	}
}