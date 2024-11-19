#include <pch.h>
#include "menu.hpp"

// Variables
const char* glow_style[] = { "default", "pulse", "outline", "outline pulse" };
const char* chams_types[] = { "regular", "flat", "crystal", "pearlescent", "reverse pearlescent", "fog", "damascus", "model" };
const char* chams_overlay_types[] = { "glow", "outline", "metallic", "snow" };
const char* cham_types[] = { "arms", "weapon" };
const char* sky_type[] = { "none", "night", "lunacy", "custom" };
const char* indicator_type[] = { "Default", "Verdana", "Impact", "Tahoma", "Arial"};
static int chams_type = 0;
const char* sounds[] = { "none", "default", "coin", "custom" };
const char* fb_angles[] = { "right", "backwards", "left" };
const char* configs[] = { "one", "two", "three", "four", "five" };
const char* knifes[] = { "default", "bayonet", "m9 bayonet", "karambit", "butterfly", "bowie", "falchion", "flip", "gut", "huntsman", "shadow daggers", "navaja", "stiletto", "talon", "ursus", "nomad", "skeleton", "survival", "paracord", "classic" };
const char* gloves[] = { "default", "blood", "sport", "slick", "leather", "moto", "specialist", "hydra", "fang" };
static int current_config = 0;
std::string cfg = std::to_string(current_config + 1);

void menu::tabs::visual() {
	gui::Checkbox(xorstr("trail"), &var::visuals::trail::enabled);
	if (var::visuals::trail::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("trail color"), var::visuals::trail::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SliderInt(xorstr("trail life"), &var::visuals::trail::life, 1, 5, xorstr("%d"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("local dlight"), &var::visuals::local_dlight::enabled);
	if (var::visuals::local_dlight::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("dlight color"), var::visuals::local_dlight::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SliderInt(xorstr("dlight radius"), &var::visuals::local_dlight::radius, 100, 200, xorstr("%d"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("bullet tracers"), &var::visuals::bullet_tracers::enabled);
	if (var::visuals::bullet_tracers::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("bullet tracer color"), var::visuals::bullet_tracers::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("bullet impacts"), &var::visuals::bullet_impacts::enabled);
	if (var::visuals::bullet_impacts::enabled) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("bullet impact color"), var::visuals::bullet_impacts::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}

	gui::Checkbox(xorstr("chams"), &var::visuals::chams::enabled);
	if (var::visuals::chams::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("chams bind"), &var::visuals::chams::keybind, &var::visuals::chams::kb_style);
		gui::Combo(xorstr("chams type"), &chams_type, cham_types, IM_ARRAYSIZE(cham_types));
		if (chams_type == 0) {
			gui::Checkbox(xorstr("arm chams"), &var::visuals::chams::arms::enabled);
			if (var::visuals::chams::arms::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("arm chams color"), var::visuals::chams::arms::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("material"), &var::visuals::chams::arms::material, chams_types, IM_ARRAYSIZE(chams_types));
			}
			gui::Checkbox(xorstr("arm overlay"), &var::visuals::chams::arms::overlay::enabled);
			if (var::visuals::chams::arms::overlay::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("overlay color"), var::visuals::chams::arms::overlay::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("overlay"), &var::visuals::chams::arms::overlay::material, chams_overlay_types, IM_ARRAYSIZE(chams_overlay_types));
				gui::Checkbox(xorstr("wireframe overlay"), &var::visuals::chams::arms::overlay::wireframe);
			}
			if (var::visuals::chams::arms::enabled || var::visuals::chams::arms::overlay::enabled) {
				gui::Checkbox(xorstr("occluded"), &var::visuals::chams::arms::occluded);
				gui::Checkbox(xorstr("draw original model"), &var::visuals::chams::arms::draw_original);
			}
			gui::Checkbox(xorstr("remove sleeves"), &var::visuals::chams::arms::remove_sleeves);
		}
		else if (chams_type == 1) {
			gui::Checkbox(xorstr("weapon chams"), &var::visuals::chams::weapon::enabled);
			if (var::visuals::chams::weapon::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("weapon chams color"), var::visuals::chams::weapon::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("material"), &var::visuals::chams::weapon::material, chams_types, IM_ARRAYSIZE(chams_types));
			}
			gui::Checkbox(xorstr("weapon overlay"), &var::visuals::chams::weapon::overlay::enabled);
			if (var::visuals::chams::weapon::overlay::enabled) {
				gui::SameLine();
				gui::ColorEdit4(xorstr("overlay color"), var::visuals::chams::weapon::overlay::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
				gui::Combo(xorstr("overlay"), &var::visuals::chams::weapon::overlay::material, chams_overlay_types, IM_ARRAYSIZE(chams_overlay_types));
				gui::Checkbox(xorstr("wireframe overlay"), &var::visuals::chams::weapon::overlay::wireframe);
			}
			if (var::visuals::chams::weapon::enabled || var::visuals::chams::weapon::overlay::enabled) {
				gui::Checkbox(xorstr("occluded"), &var::visuals::chams::weapon::occluded);
				gui::Checkbox(xorstr("draw original model"), &var::visuals::chams::weapon::draw_original);
			}
		}
	}
	gui::Checkbox(xorstr("custom viewmodel"), &var::visuals::view::viewmodel);
	if (var::visuals::view::viewmodel) {
		gui::SameLine();
		gui::SliderInt(xorstr("viewmodel fov"), &var::visuals::view::model, 60, 120, xorstr("%d"), ImGuiSliderFlags_NoInput);
		gui::SliderInt(xorstr("roll angle"), &var::visuals::view::angle, -180, 180, xorstr("%d"), ImGuiSliderFlags_NoInput);
		gui::Checkbox(xorstr("spin"), &var::visuals::view::spin);
		if (var::visuals::view::spin) {
			gui::SliderInt(xorstr("spin speed"), &var::visuals::view::spin_speed, 5, 1000, xorstr("%d"), ImGuiSliderFlags_NoInput);
		}
	}

	gui::SliderFloat(xorstr("aspect ratio"), &var::visuals::view::aspect, 0.f, 3.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);

	//gui::SliderInt(xorstr("fov"), &var::visuals::view::fov, 90, 120, xorstr("%d"), ImGuiSliderFlags_NoInput);
	

}

void menu::tabs::troll() {
	gui::Checkbox(xorstr("bunnyhop"), &var::movement::bunnyhop::enabled);
	if (var::movement::bunnyhop::enabled) {
		gui::SliderInt(xorstr("bhop chance"), &var::movement::bunnyhop::hitchance, 1, 100, xorstr("%d%%"), ImGuiSliderFlags_NoInput);
	}
	gui::Checkbox(xorstr("blockbot"), &var::movement::blockbot::enabled);
	if (var::movement::blockbot::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("blockbot bind"), &var::movement::blockbot::keybind, &var::movement::blockbot::kb_style);
	}

	gui::Checkbox(xorstr("slide walk"), &var::movement::slidewalk);
	gui::Checkbox(xorstr("kill say"), &var::misc::killsay);
	gui::Checkbox(xorstr("door spammer"), &var::misc::doorspammer::enabled);
	if (var::misc::doorspammer::enabled) {
		gui::SameLine();
		gui::KeyBind(xorstr("door spam bind"), &var::misc::doorspammer::keybind, &var::misc::doorspammer::kb_style);
	}
}

void menu::tabs::skins() {
	gui::Combo(xorstr("knife model"), &var::misc::knife::model, knifes, IM_ARRAYSIZE(knifes));
	gui::Combo(xorstr("knife skin"), &var::misc::knife::skin, [](void* data, int idx, const char** out_text) {
		*out_text = parser_skins[idx].name.c_str();
		return true;
		}, nullptr, parser_skins.size(), 10);
	/*gui::Checkbox(xorstr("knife color"), &var::misc::knife::custom_color);
	if (var::misc::knife::custom_color) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 1"), var::misc::knife::color1, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 2"), var::misc::knife::color2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 3"), var::misc::knife::color3, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
		gui::SameLine();
		gui::ColorEdit4(xorstr("custom color 4"), var::misc::knife::color4, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}*/
	gui::Combo(xorstr("glove model"), &var::misc::glove::model, gloves, IM_ARRAYSIZE(gloves));
	gui::Combo(xorstr("glove skin"), &var::misc::glove::skin, [](void* data, int idx, const char** out_text) {
		*out_text = parser_gloves[idx].name.c_str();
		return true;
		}, nullptr, parser_gloves.size(), 10);
}

void menu::tabs::misc() {
	gui::Checkbox(xorstr("auto accept"), &var::misc::autoaccept);
	gui::Checkbox(xorstr("rank reveal"), &var::misc::rank_reveal);
	gui::Checkbox(xorstr("unlock inventory"), &var::misc::unlock_inventory);
	gui::Checkbox(xorstr("clantag"), &var::misc::clantag);
	gui::Checkbox(xorstr("watermark"), &var::visuals::watermark);

	gui::Checkbox(xorstr("disable postprocess"), &var::visuals::disable_postprocess);

	gui::Checkbox(xorstr("motion blur"), &var::visuals::motionblur::enabled);
	if (var::visuals::motionblur::enabled) {
		gui::SliderFloat(xorstr("blur strength"), &var::visuals::motionblur::strength, 1.f, 10.f, xorstr("%.1f"), ImGuiSliderFlags_NoInput);
	}
}

void menu::tabs::config() {
	gui::Combo(xorstr("config"), &current_config, configs, IM_ARRAYSIZE(configs));
	if (gui::Button(xorstr("load"))) {
		config::reset();
		config::load(configs[current_config]);
		interfaces::clientstate->full_update();
		//notify::run(xorstr("loaded config ") + cfg, var::misc::event_logs, var::misc::chat_logs);
	}
	gui::SameLine();
	if (gui::Button(xorstr("save"))) gui::OpenPopup(xorstr("save popup"));
	gui::SameLine();
	if (gui::Button(xorstr("reset"))) {
		config::reset();
		//notify::run(xorstr("reset config ") + cfg, var::misc::event_logs, var::misc::chat_logs);
	}
	if (gui::Button(xorstr("import"))) config::import_cfg();
	gui::SameLine();
	if (gui::Button(xorstr("export"))) config::export_cfg();
	if (gui::Button(xorstr("config folder"))) ShellExecuteA(0, xorstr("open"), xorstr("C:\\Users\\Public\\Documents"), NULL, NULL, SW_NORMAL);

	if (gui::BeginPopup(xorstr("save popup"))) {
		if (gui::Button(xorstr("save config"))) {
			gui::CloseCurrentPopup();
			config::save(configs[current_config]);
			//notify::run(xorstr("saved config ") + cfg, var::misc::event_logs, var::misc::chat_logs);
		}
		gui::SameLine();
		if (gui::Button(xorstr("cancel"))) { gui::CloseCurrentPopup(); }
		gui::EndPopup();
	}
}

void menu::tabs::config_extra() {
	gui::Text(xorstr("last update: %s"), __DATE__);
	gui::Text(xorstr("menu key"));
	gui::SameLine();
	gui::KeyBind(xorstr("menu bind"), &var::menu::keybind);
	gui::Text(xorstr("menu accent"));
	gui::SameLine();
	gui::ColorEdit4(xorstr("menu accent"), var::menu::accent, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	gui::Checkbox(xorstr("background"), &var::menu::background);
	if (var::menu::background) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("background color"), var::menu::background_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
	gui::Checkbox(xorstr("background effect"), &var::menu::background_effect);
	if (var::menu::background_effect) {
		gui::SameLine();
		gui::ColorEdit4(xorstr("effect color"), var::menu::background_effect_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview);
	}
}
