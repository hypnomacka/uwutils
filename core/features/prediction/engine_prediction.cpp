#include <pch.h>
#include "engine_prediction.hpp"

bool prediction::in_prediction() {
	return in_progress;
}

void prediction::start(c_usercmd* cmd) {
	if (!csgo::local_player) return;

	in_progress = true;

	if (!prediction_random_seed)
		prediction_random_seed = *reinterpret_cast<int**>(util::pattern_scan(xorstr("client.dll"), xorstr("8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04")) + 2);

	*prediction_random_seed = cmd->randomseed & 0x7FFFFFFF;
	old_cur_time = interfaces::globals->cur_time;
	old_frame_time = interfaces::globals->frame_time;

	interfaces::globals->cur_time = csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick;
	interfaces::globals->frame_time = interfaces::globals->interval_per_tick;
	interfaces::game_movement->start_track_prediction_errors(csgo::local_player);

	memset(&data, 0, sizeof(data));
	interfaces::move_helper->set_host(csgo::local_player);
	interfaces::prediction->setup_move(csgo::local_player, cmd, interfaces::move_helper, &data);
	interfaces::game_movement->process_movement(csgo::local_player, &data);
	interfaces::prediction->finish_move(csgo::local_player, cmd, &data);
}

void prediction::end() {
	if (!csgo::local_player) return;

	interfaces::game_movement->finish_track_prediction_errors(csgo::local_player);
	interfaces::move_helper->set_host(nullptr);
	*prediction_random_seed = -1;
	interfaces::globals->cur_time = old_cur_time;
	interfaces::globals->frame_time = old_frame_time;
	interfaces::game_movement->reset();

	in_progress = false;
}

void prediction::restore(int predicted_frame) {
	static auto restore = reinterpret_cast<DWORD(__stdcall*)(int, int)>(util::pattern_scan(xorstr("client.dll"), xorstr("55 8B EC 8B 4D ? 56 E8 ? ? ? ? 8B 75")));
	restore(0, predicted_frame);
}