#include <pch.h>
#include "events.hpp"
#include "../features.hpp"

event_manager event_listener;

// Event hitlogs
std::string hitbox(int hitgroup) {
	switch (hitgroup) {
		case hitgroup_head:
			return xorstr("head");
		case hitgroup_chest:
			return xorstr("chest");
		case hitgroup_stomach:
			return xorstr("stomach");
		case hitgroup_leftleg:
			return xorstr("left leg");
		case hitgroup_rightleg:
			return xorstr("right leg");
		case hitgroup_leftarm:
			return xorstr("left arm");
		case hitgroup_rightarm:
			return xorstr("right arm");
		default:
			return xorstr("body");
	}
}

void playerhurt(i_game_event* event) {
	// Check if we are doing event
	if (!event) return;

	auto attacker = interfaces::entity_list->get_client_entity(interfaces::engine->get_player_for_user_id(event->get_int(xorstr("attacker"))));
	auto victim = interfaces::engine->get_player_for_user_id(event->get_int(xorstr("userid")));
	if (!attacker || attacker != csgo::local_player || !victim) return;

	auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(victim));
	if (!entity) return;

	player_info_t info;
	interfaces::engine->get_player_info(entity->index(), &info);

	int damage = event->get_int(xorstr("dmg_health"));
	int health = event->get_int(xorstr("health"));

	// Print hitlogs - i am too lazy to convert this to non autistic code rn, remind me later x ~weird
	std::string hurt_info = xorstr("hit ") + std::string(info.name) + xorstr(" in ") + hitbox(event->get_int(xorstr("hitgroup"))) + xorstr(" for ") + std::to_string(damage) + xorstr(" dmg (") + std::to_string(health) + xorstr(" hp remaining)");
}

void playerdeath(i_game_event* event) {
	// Check if we are doing event
	if (!event) return;

	const auto attacker = interfaces::entity_list->get_client_entity(interfaces::engine->get_player_for_user_id(event->get_int(xorstr("attacker"))));
	const auto victim = interfaces::engine->get_player_for_user_id(event->get_int(xorstr("userid")));
	if (!attacker || attacker != csgo::local_player || !victim) return;

	const auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(victim));
	if (!entity) return;

	// Kill say
	const std::vector<std::string> phrase = { xorstr("killsay 1"), 
											  xorstr("killsay 2"), 
											  xorstr("killsay 3"), 
											  xorstr("killsay 4") };
	const auto say = std::vformat(xorstr("say {}"), std::make_format_args(phrase[rand() % phrase.size()]));

	if (var::misc::killsay)
		interfaces::engine->execute_cmd(say.c_str());
}

void playervote(i_game_event* event) {
	// Check if we are doing event
	if (!event) return;

	const auto vote = event->get_int(xorstr("vote_option"));
	const auto id = event->get_int(xorstr("entityid"));

	player_info_t player;
	interfaces::engine->get_player_info(id, &player);
	if (!player.name) return;

	// Reveal votes
	const auto vote_message = std::vformat(xorstr("{} voted {}"), std::make_format_args(player.name, "idk"));
	notify::run(vote_message, false, true);
}

void bullet_impact(i_game_event* event) {
	// Check if we are doing event
	if (!event) return;

	auto userid = interfaces::engine->get_player_for_user_id(event->get_int(xorstr("userid")));
	if (!userid) return;

	auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(userid));
	if (!entity || entity != csgo::local_player) return;

	// Impact position
	vec3_t position{ event->get_float(xorstr("x")), event->get_float(xorstr("y")), event->get_float(xorstr("z")) };

	// Render bullet tracer
	if (var::visuals::bullet_tracers::enabled)
		render::draw_beam(color(var::visuals::bullet_tracers::color), 1, 1, FBEAM_SHADEOUT, csgo::local_player->get_eye_pos(), position);

	// Render bullet impact
	if (var::visuals::bullet_impacts::enabled)
		interfaces::debug_overlay->add_box_overlay(position, vec3_t(-2, -2, -2), vec3_t(2, 2, 2), vec3_t(0, 0, 0), color(var::visuals::bullet_impacts::color), 1);
}

void event_manager::fire_game_event(i_game_event* event) {
	auto event_name = event->get_name();

	// Sanity checks
	if (!interfaces::engine->is_in_game() || !csgo::local_player) return;

	if (!strcmp(event_name, xorstr("player_death"))) playerdeath(event);

	if (!strcmp(event_name, xorstr("player_hurt"))) playerhurt(event);

	if (!strcmp(event_name, xorstr("bullet_impact"))) bullet_impact(event);

}

void event_manager::initialize() {
	debug_id = EVENT_DEBUG_ID_INIT;
	interfaces::event_manager->add_listener(this, xorstr("player_death"), false);
	interfaces::event_manager->add_listener(this, xorstr("player_hurt"), false);
	interfaces::event_manager->add_listener(this, xorstr("vote_cast"), false);
	interfaces::event_manager->add_listener(this, xorstr("bullet_impact"), false);
	console::log(xorstr("events initialized\n"));
}

void event_manager::release() {
	interfaces::event_manager->remove_listener(this);
}