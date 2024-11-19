#include <pch.h>
#include "config.hpp"
#include "variables.hpp"
#include "../../dependencies/utilities/base64/base64.h"
#include "../../dependencies/utilities/json.hpp"
#include <winuser.h>
#include <winbase.h>
#include <format>

const char* path = "C:\\Users\\Public\\Documents\\Uwutils_";

nlohmann::json varsToJSON() {
	nlohmann::json config;

	// MENU
	config["menu"]["accent"] = var::menu::accent;
	config["menu"]["background"] = var::menu::background;
	config["menu"]["background_color"] = var::menu::background_color;
	config["menu"]["background_effect"] = var::menu::background_effect;
	config["menu"]["background_effect_color"] = var::menu::background_effect_color;
	config["menu"]["keybind"] = var::menu::keybind;

	// VISUAL
	config["visuals"]["chams"]["enabled"] = var::visuals::chams::enabled;
	config["visuals"]["chams"]["keybind"] = var::visuals::chams::keybind;
	config["visuals"]["chams"]["kb_style"] = var::visuals::chams::kb_style;
	config["visuals"]["chams"]["model_occlusion"] = var::visuals::chams::model_occlusion;
	config["visuals"]["chams"]["wireframe_overlay"] = var::visuals::chams::wireframe_overlay;
	config["visuals"]["chams"]["arms"]["enabled"] = var::visuals::chams::arms::enabled;
	config["visuals"]["chams"]["arms"]["occluded"] = var::visuals::chams::arms::occluded;
	config["visuals"]["chams"]["arms"]["draw_original"] = var::visuals::chams::arms::draw_original;
	config["visuals"]["chams"]["arms"]["remove_sleeves"] = var::visuals::chams::arms::remove_sleeves;
	config["visuals"]["chams"]["arms"]["material"] = var::visuals::chams::arms::material;
	config["visuals"]["chams"]["arms"]["color"] = var::visuals::chams::arms::color;
	config["visuals"]["chams"]["arms"]["overlay"]["enabled"] = var::visuals::chams::arms::overlay::enabled;
	config["visuals"]["chams"]["arms"]["overlay"]["wireframe"] = var::visuals::chams::arms::overlay::wireframe;
	config["visuals"]["chams"]["arms"]["overlay"]["material"] = var::visuals::chams::arms::overlay::material;
	config["visuals"]["chams"]["arms"]["overlay"]["color"] = var::visuals::chams::arms::overlay::color;
	config["visuals"]["chams"]["weapon"]["enabled"] = var::visuals::chams::weapon::enabled;
	config["visuals"]["chams"]["weapon"]["occluded"] = var::visuals::chams::weapon::occluded;
	config["visuals"]["chams"]["weapon"]["draw_original"] = var::visuals::chams::weapon::draw_original;
	config["visuals"]["chams"]["weapon"]["material"] = var::visuals::chams::weapon::material;
	config["visuals"]["chams"]["weapon"]["color"] = var::visuals::chams::weapon::color;
	config["visuals"]["chams"]["weapon"]["overlay"]["enabled"] = var::visuals::chams::weapon::overlay::enabled;
	config["visuals"]["chams"]["weapon"]["overlay"]["wireframe"] = var::visuals::chams::weapon::overlay::wireframe;
	config["visuals"]["chams"]["weapon"]["overlay"]["material"] = var::visuals::chams::weapon::overlay::material;
	config["visuals"]["chams"]["weapon"]["overlay"]["color"] = var::visuals::chams::weapon::overlay::color;
	config["visuals"]["trail"]["enabled"] = var::visuals::trail::enabled;
	config["visuals"]["trail"]["color"] = var::visuals::trail::color;
	config["visuals"]["trail"]["life"] = var::visuals::trail::life;
	config["visuals"]["local_dlight"]["enabled"] = var::visuals::local_dlight::enabled;
	config["visuals"]["local_dlight"]["color"] = var::visuals::local_dlight::color;
	config["visuals"]["local_dlight"]["radius"] = var::visuals::local_dlight::radius;
	config["visuals"]["bullet_tracers"]["enabled"] = var::visuals::bullet_tracers::enabled;
	config["visuals"]["bullet_tracers"]["color"] = var::visuals::bullet_tracers::color;
	config["visuals"]["bullet_impacts"]["enabled"] = var::visuals::bullet_impacts::enabled;
	config["visuals"]["bullet_impacts"]["color"] = var::visuals::bullet_impacts::color;
	config["visuals"]["view"]["fov"] = var::visuals::view::fov;
	config["visuals"]["view"]["model"] = var::visuals::view::model;
	config["visuals"]["view"]["angle"] = var::visuals::view::angle;
	config["visuals"]["view"]["aspect"] = var::visuals::view::aspect;
	config["visuals"]["view"]["aspect"] = var::visuals::view::aspect;
	config["visuals"]["view"]["spin"] = var::visuals::view::spin;
	config["visuals"]["view"]["enabled"] = var::visuals::view::viewmodel;
	config["visuals"]["motionblur"]["enabled"] = var::visuals::motionblur::enabled;
	config["visuals"]["motionblur"]["strength"] = var::visuals::motionblur::strength;
	config["visuals"]["disable_postprocess"] = var::visuals::disable_postprocess;
	config["visuals"]["watermark"] = var::visuals::watermark;

	// MISC
	config["misc"]["clantag"] = var::misc::clantag;
	config["misc"]["killsay"] = var::misc::killsay;
	config["misc"]["autoaccept"] = var::misc::autoaccept;
	config["misc"]["rank_reveal"] = var::misc::rank_reveal;
	config["misc"]["unlock_inventory"] = var::misc::unlock_inventory;
	config["misc"]["doorspammer"]["enabled"] = var::misc::doorspammer::enabled;
	config["misc"]["doorspammer"]["keybind"] = var::misc::doorspammer::keybind;
	config["misc"]["doorspammer"]["kb_style"] = var::misc::doorspammer::kb_style;
	config["misc"]["knife"]["model"] = var::misc::knife::model;
	config["misc"]["knife"]["skin"] = var::misc::knife::skin;
	config["misc"]["knife"]["custom_color"] = var::misc::knife::custom_color;
	config["misc"]["knife"]["color1"] = var::misc::knife::color1;
	config["misc"]["knife"]["color2"] = var::misc::knife::color2;
	config["misc"]["knife"]["color3"] = var::misc::knife::color3;
	config["misc"]["knife"]["color4"] = var::misc::knife::color4;
	config["misc"]["glove"]["model"] = var::misc::glove::model;
	config["misc"]["glove"]["skin"] = var::misc::glove::skin;

	// MOVEMENT
	config["movement"]["bunnyhop"]["enabled"] = var::movement::bunnyhop::enabled;
	config["movement"]["bunnyhop"]["hitchance"] = var::movement::bunnyhop::hitchance;
	config["movement"]["blockbot"]["enabled"] = var::movement::blockbot::enabled;
	config["movement"]["blockbot"]["keybind"] = var::movement::blockbot::keybind;
	config["movement"]["blockbot"]["kb_style"] = var::movement::blockbot::kb_style;
	config["movement"]["ticks"] = var::movement::ticks;
	config["movement"]["lock_factor"] = var::movement::lock_factor;
	config["movement"]["slidewalk"] = var::movement::slidewalk;

	return config;
}

void varsFromJSON(nlohmann::json config) {
	if (config.contains("menu")) {
		// Menu section
		nlohmann::json menu = config["menu"];

		if (menu.contains("accent")) std::copy(menu["accent"].begin(), menu["accent"].end(), var::menu::accent); // read color array
		if (menu.contains("background")) var::menu::background = menu["background"].get<bool>(); // cast to bool
		if (menu.contains("background_color")) std::copy(menu["background_color"].begin(), menu["background_color"].end(), var::menu::background_color); // read color array
		if (menu.contains("background_effect")) var::menu::background_effect = menu["background_effect"].get<bool>(); // cast to bool
		if (menu.contains("background_effect_color")) std::copy(menu["background_effect_color"].begin(), menu["background_effect_color"].end(), var::menu::background_effect_color); // read color array
		if (menu.contains("keybind")) var::menu::keybind = menu["keybind"].get<int>(); // cast to int
	}

	if (config.contains("visuals")) {
		// Visuals section
		nlohmann::json visuals = config["visuals"];

		if (visuals.contains("chams")) {
			// Chams
			nlohmann::json chams = visuals["chams"];

			if (chams.contains("enabled")) var::visuals::chams::enabled = chams["enabled"].get<bool>(); // cast to bool
			if (chams.contains("keybind")) var::visuals::chams::keybind = chams["keybind"].get<int>(); // cast to int
			if (chams.contains("kb_style")) var::visuals::chams::kb_style = chams["kb_style"].get<int>(); // cast to int
			if (chams.contains("model_occlusion")) var::visuals::chams::model_occlusion = chams["model_occlusion"].get<bool>(); // cast to bool
			if (chams.contains("wireframe_overlay")) var::visuals::chams::wireframe_overlay = chams["wireframe_overlay"].get<bool>(); // cast to bool

			if (chams.contains("arms")) {
				// Arms
				nlohmann::json arms = chams["arms"];

				if (arms.contains("enabled")) var::visuals::chams::arms::enabled = arms["enabled"].get<bool>(); // cast to bool
				if (arms.contains("occluded")) var::visuals::chams::arms::occluded = arms["occluded"].get<bool>(); // cast to bool
				if (arms.contains("draw_original")) var::visuals::chams::arms::draw_original = arms["draw_original"].get<bool>(); // cast to bool
				if (arms.contains("remove_sleeves")) var::visuals::chams::arms::remove_sleeves = arms["remove_sleeves"].get<bool>(); // cast to bool
				if (arms.contains("material")) var::visuals::chams::arms::material = arms["material"].get<int>(); // cast to int
				if (arms.contains("color")) std::copy(arms["color"].begin(), arms["color"].end(), var::visuals::chams::arms::color); // read color array

				if (arms.contains("overlay")) {
					// Overlay
					nlohmann::json overlay = arms["overlay"];

					if (overlay.contains("enabled")) var::visuals::chams::arms::overlay::enabled = overlay["enabled"].get<bool>(); // cast to bool
					if (overlay.contains("wireframe")) var::visuals::chams::arms::overlay::wireframe = overlay["wireframe"].get<bool>(); // cast to bool
					if (overlay.contains("material")) var::visuals::chams::arms::overlay::material = overlay["material"].get<int>(); // cast to int
					if (overlay.contains("color")) std::copy(overlay["color"].begin(), overlay["color"].end(), var::visuals::chams::arms::overlay::color); // read color array
				}
			}
			if (chams.contains("weapon")) {
				// Weapon
				nlohmann::json weapon = chams["weapon"];

				if (weapon.contains("enabled")) var::visuals::chams::weapon::enabled = weapon["enabled"].get<bool>(); // cast to bool
				if (weapon.contains("occluded")) var::visuals::chams::weapon::occluded = weapon["occluded"].get<bool>(); // cast to bool
				if (weapon.contains("draw_original")) var::visuals::chams::weapon::draw_original = weapon["draw_original"].get<bool>(); // cast to bool
				if (weapon.contains("material")) var::visuals::chams::weapon::material = weapon["material"].get<int>(); // cast to int
				if (weapon.contains("color")) std::copy(weapon["color"].begin(), weapon["color"].end(), var::visuals::chams::weapon::color); // read color array

				if (weapon.contains("overlay")) {
					// Overlay
					nlohmann::json overlay = weapon["overlay"];

					if (overlay.contains("enabled")) var::visuals::chams::weapon::overlay::enabled = overlay["enabled"].get<bool>(); // cast to bool
					if (overlay.contains("wireframe")) var::visuals::chams::weapon::overlay::wireframe = overlay["wireframe"].get<bool>(); // cast to bool
					if (overlay.contains("material")) var::visuals::chams::weapon::overlay::material = overlay["material"].get<int>(); // cast to int
					if (overlay.contains("color")) std::copy(overlay["color"].begin(), overlay["color"].end(), var::visuals::chams::weapon::overlay::color); // read color array
				}
			}
		}

		if (visuals.contains("trail")) {
			// Trail
			nlohmann::json trail = visuals["trail"];

			if (trail.contains("enabled")) var::visuals::trail::enabled = trail["enabled"].get<bool>(); // cast to bool
			if (trail.contains("color")) std::copy(trail["color"].begin(), trail["color"].end(), var::visuals::trail::color); // read color array
			if (trail.contains("life")) var::visuals::trail::life = std::clamp(trail["life"].get<int>(), 1, 5); // clamp min and max values
		}
		if (visuals.contains("local_dlight")) {
			// Local dlight
			nlohmann::json local_dlight = visuals["local_dlight"];

			if (local_dlight.contains("enabled")) var::visuals::local_dlight::enabled = local_dlight["enabled"].get<bool>(); // cast to bool
			if (local_dlight.contains("color")) std::copy(local_dlight["color"].begin(), local_dlight["color"].end(), var::visuals::local_dlight::color); // read color array
			if (local_dlight.contains("radius")) var::visuals::local_dlight::radius = std::clamp(local_dlight["radius"].get<int>(), 100, 200); // clamp min and max values
		}
		if (visuals.contains("bullet_tracers")) {
			// Bullet tracers
			nlohmann::json bullet_tracers = visuals["bullet_tracers"];

			if (bullet_tracers.contains("enabled")) var::visuals::bullet_tracers::enabled = bullet_tracers["enabled"].get<bool>(); // cast to bool
			if (bullet_tracers.contains("color")) std::copy(bullet_tracers["color"].begin(), bullet_tracers["color"].end(), var::visuals::bullet_tracers::color); // read color array
		}
		if (visuals.contains("bullet_impacts")) {
			// Bullet impacts
			nlohmann::json bullet_impacts = visuals["bullet_impacts"];

			if (bullet_impacts.contains("enabled")) var::visuals::bullet_impacts::enabled = bullet_impacts["enabled"].get<bool>(); // cast to bool
			if (bullet_impacts.contains("color")) std::copy(bullet_impacts["color"].begin(), bullet_impacts["color"].end(), var::visuals::bullet_impacts::color); // read color array
		}
	
		if (visuals.contains("view")) {
			// View
			nlohmann::json view = visuals["view"];

			if (view.contains("fov")) var::visuals::view::fov = std::clamp(view["fov"].get<int>(), 90, 120); // clamp min and max values
			if (view.contains("model")) var::visuals::view::model = std::clamp(view["model"].get<int>(), 60, 120); // clamp min and max values
			if (view.contains("angle")) var::visuals::view::angle = std::clamp(view["angle"].get<int>(), -180, 180); // clamp min and max values
			if (view.contains("aspect")) var::visuals::view::aspect = std::clamp(view["aspect"].get<float>(), 0.f, 3.f); // clamp min and max values
		}
		if (visuals.contains("motionblur")) {
			// Motion blur
			nlohmann::json motionblur = visuals["fog_changer"];

			if (motionblur.contains("enabled")) var::visuals::motionblur::enabled = motionblur["enabled"].get<bool>(); // cast to bool
			if (motionblur.contains("strength")) var::visuals::motionblur::strength = std::clamp(motionblur["strength"].get<float>(), 1.f, 10.f); // clamp min and max values
		}
		if (visuals.contains("fog_changer")) {
			// Fog changer
			nlohmann::json fog_changer = visuals["fog_changer"];

			if (fog_changer.contains("enabled")) var::visuals::fog_changer::enabled = fog_changer["enabled"].get<bool>(); // cast to bool
			if (fog_changer.contains("color")) std::copy(fog_changer["color"].begin(), fog_changer["color"].end(), var::visuals::fog_changer::color); // read color array
			if (fog_changer.contains("start")) var::visuals::fog_changer::start = std::clamp(fog_changer["start"].get<int>(), 0, 2500); // clamp min and max values
		}
		
		if (visuals.contains("disable_postprocess")) var::visuals::disable_postprocess = visuals["disable_postprocess"].get<bool>(); // cast to bool
		if (visuals.contains("watermark")) var::visuals::watermark = visuals["watermark"].get<bool>(); // cast to bool
	}

	if (config.contains("misc")) {
		// Misc section
		nlohmann::json misc = config["misc"];

		if (misc.contains("clantag")) var::misc::clantag = misc["clantag"].get<bool>(); // cast to bool
		if (misc.contains("killsay")) var::misc::killsay = misc["killsay"].get<bool>(); // cast to bool
		if (misc.contains("autoaccept")) var::misc::autoaccept = misc["autoaccept"].get<bool>(); // cast to bool
		if (misc.contains("rank_reveal")) var::misc::rank_reveal = misc["rank_reveal"].get<bool>(); // cast to bool
		if (misc.contains("unlock_inventory")) var::misc::unlock_inventory = misc["unlock_inventory"].get<bool>(); // cast to bool

		if (misc.contains("doorspammer")) {
			// Doorspammer
			nlohmann::json doorspammer = misc["doorspammer"];

			if (doorspammer.contains("enabled")) var::misc::doorspammer::enabled = doorspammer["enabled"].get<bool>(); // cast to bool
			if (doorspammer.contains("keybind")) var::misc::doorspammer::keybind = doorspammer["keybind"].get<int>(); // cast to int
			if (doorspammer.contains("kb_style")) var::misc::doorspammer::kb_style = doorspammer["kb_style"].get<int>(); // cast to int
		}
		
		if (misc.contains("knife")) {
			// Knife
			nlohmann::json knife = misc["knife"];

			if (knife.contains("model")) var::misc::knife::model = knife["model"].get<int>(); // cast to int
			if (knife.contains("skin")) var::misc::knife::skin = knife["skin"].get<int>(); // cast to int
			if (knife.contains("custom_color")) var::misc::knife::custom_color = knife["custom_color"].get<bool>(); // cast to bool
			if (knife.contains("color1")) std::copy(knife["color1"].begin(), knife["color1"].end(), var::misc::knife::color1); // read color array
			if (knife.contains("color2")) std::copy(knife["color2"].begin(), knife["color2"].end(), var::misc::knife::color2); // read color array
			if (knife.contains("color3")) std::copy(knife["color3"].begin(), knife["color3"].end(), var::misc::knife::color3); // read color array
			if (knife.contains("color4")) std::copy(knife["color4"].begin(), knife["color4"].end(), var::misc::knife::color4); // read color array
		}
		if (misc.contains("glove")) {
			// Glove
			nlohmann::json glove = misc["glove"];

			if (glove.contains("model")) var::misc::glove::model = glove["model"].get<int>(); // cast to int
			if (glove.contains("skin")) var::misc::glove::skin = glove["skin"].get<int>(); // cast to int
		}
	}

	if (config.contains("movement")) {
		// Movement section
		nlohmann::json movement = config["movement"];

		if (movement.contains("bunnyhop")) {
			// Bunnyhop
			nlohmann::json bunnyhop = movement["bunnyhop"];

			if (bunnyhop.contains("enabled")) var::movement::bunnyhop::enabled = bunnyhop["enabled"].get<bool>(); // cast to bool
			if (bunnyhop.contains("hitchance")) var::movement::bunnyhop::hitchance = std::clamp(bunnyhop["hitchance"].get<int>(), 1, 100); // clamp min and max values
		}
		
		if (movement.contains("blockbot")) {
			// Blockbot
			nlohmann::json blockbot = movement["blockbot"];

			if (blockbot.contains("enabled")) var::movement::blockbot::enabled = blockbot["enabled"].get<bool>(); // cast to bool
			if (blockbot.contains("keybind")) var::movement::blockbot::keybind = blockbot["keybind"].get<int>(); // cast to int
			if (blockbot.contains("kb_style")) var::movement::blockbot::kb_style = blockbot["kb_style"].get<int>(); // cast to int
		}
		
		if (movement.contains("ticks")) var::movement::ticks = std::clamp(movement["ticks"].get<int>(), 1, 64); // clamp min and max values
		if (movement.contains("lock_factor")) var::movement::lock_factor = std::clamp(movement["lock_factor"].get<float>(), 0.f, 1.f); // clamp min and max values
		if (movement.contains("slidewalk")) var::movement::slidewalk = movement["slidewalk"].get<bool>(); // cast to bool
	}
}

void config::reset() {
	// MENU
	std::fill_n(var::menu::accent, 4, 1.f);
	var::menu::background = false;
	std::fill_n(var::menu::background_color, 4, 0.f);
	var::menu::background_effect = false;
	std::fill_n(var::menu::background_effect_color, 4, 1.f);
	var::menu::keybind = 0x2D;

	// VISUAL
	var::visuals::esp::dlight::enabled = false;
	std::fill_n(var::visuals::esp::dlight::color, 4, 1.f);
	var::visuals::esp::dlight::radius = 100;
	var::visuals::chams::enabled = false;
	var::visuals::chams::keybind = 0;
	var::visuals::chams::kb_style = 1;
	var::visuals::chams::model_occlusion = false;
	var::visuals::chams::wireframe_overlay = false;
	var::visuals::chams::arms::enabled = false;
	var::visuals::chams::arms::occluded = false;
	var::visuals::chams::arms::draw_original = false;
	var::visuals::chams::arms::remove_sleeves = false;
	var::visuals::chams::arms::material = 0;
	std::fill_n(var::visuals::chams::arms::color, 4, 1.f);
	var::visuals::chams::arms::overlay::enabled = false;
	var::visuals::chams::arms::overlay::wireframe = false;
	var::visuals::chams::arms::overlay::material = 0;
	std::fill_n(var::visuals::chams::arms::overlay::color, 4, 1.f);
	var::visuals::chams::weapon::enabled = false;
	var::visuals::chams::weapon::occluded = false;
	var::visuals::chams::weapon::draw_original = false;
	var::visuals::chams::weapon::material = 0;
	std::fill_n(var::visuals::chams::weapon::color, 4, 1.f);
	var::visuals::chams::weapon::overlay::enabled = false;
	var::visuals::chams::weapon::overlay::wireframe = false;
	var::visuals::chams::weapon::overlay::material = 0;
	std::fill_n(var::visuals::chams::weapon::overlay::color, 4, 1.f);
	var::visuals::trail::enabled = false;
	std::fill_n(var::visuals::trail::color, 4, 1.f);
	var::visuals::trail::life = 1;
	var::visuals::local_dlight::enabled = false;
	std::fill_n(var::visuals::local_dlight::color, 4, 1.f);
	var::visuals::local_dlight::radius = 1;
	var::visuals::bullet_tracers::enabled = false;
	std::fill_n(var::visuals::bullet_tracers::color, 4, 1.f);
	var::visuals::bullet_impacts::enabled = false;
	std::fill_n(var::visuals::bullet_impacts::color, 4, 1.f);
	var::visuals::view::fov = 90;
	var::visuals::view::model = 60;
	var::visuals::view::angle = 0;
	var::visuals::view::aspect = 0;
	var::visuals::motionblur::enabled = false;
	var::visuals::motionblur::strength = 1;
	var::visuals::fog_changer::enabled = false;
	std::fill_n(var::visuals::fog_changer::color, 4, 1.f);
	var::visuals::fog_changer::start = 0;
	var::visuals::disable_postprocess = false;
	var::visuals::watermark = false;

	// MISC
	var::misc::clantag = false;
	var::misc::killsay = false;
	var::misc::autoaccept = false;
	var::misc::rank_reveal = false;
	var::misc::unlock_inventory = false;
	var::misc::doorspammer::enabled = false;
	var::misc::doorspammer::keybind = 0;
	var::misc::doorspammer::kb_style = 2;
	var::misc::knife::model = 0;
	var::misc::knife::skin = 0;
	var::misc::knife::custom_color = false;
	std::fill_n(var::misc::knife::color1, 4, 1.f);
	std::fill_n(var::misc::knife::color2, 4, 1.f);
	std::fill_n(var::misc::knife::color3, 4, 1.f);
	std::fill_n(var::misc::knife::color4, 4, 1.f);
	var::misc::glove::model = 0;
	var::misc::glove::skin = 0;

	// MOVEMENT
	var::movement::bunnyhop::enabled = false;
	var::movement::bunnyhop::hitchance = 100;
	var::movement::blockbot::enabled = false;
	var::movement::blockbot::keybind = 0;
	var::movement::blockbot::kb_style = 2;
	var::movement::ticks = 32;
	var::movement::lock_factor = 0.5f;
	var::movement::slidewalk = false;
}

void config::load(const std::string name) {
	try {
		nlohmann::json config;
		std::ifstream ifs(path + name);

		std::string encoded((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		std::string decoded = base64_decode(encoded);
		std::stringstream stream(decoded);
		stream >> config;

		varsFromJSON(config);
	} catch (...) {
		config::reset();
	}
}

void config::save(const std::string name) {
	try {
		nlohmann::json config = varsToJSON();
		std::string encoded = base64_encode(config.dump());

		std::cin >> encoded;
		std::ofstream write(path + name);

		write << encoded;
		write.close();
	} catch (const std::exception& e) {
		//MessageBoxA(nullptr, std::vformat("an error occurred while trying to save a config: {}", std::make_format_args(std::string(e.what()).data(), "UwU", MB_OK);
	}
}

std::string get_clipboard()
{
	try {
		OpenClipboard(nullptr);
		HANDLE hData = GetClipboardData(CF_TEXT);

		char* pszText = static_cast<char*>(GlobalLock(hData));
		std::string text(pszText);
		GlobalUnlock(hData);
		CloseClipboard();

		return text;
	}
	catch (std::exception exception) {
		return "error exporting";
	}
}

void set_clipboard(std::string text) {
	try {
		auto glob = GlobalAlloc(GMEM_FIXED, text.length() + 1);
		memcpy(glob, text.c_str(), text.length());

		OpenClipboard(GetActiveWindow());
		EmptyClipboard();
		SetClipboardData(CF_TEXT, glob);
		CloseClipboard();
	}
	catch (std::exception exception) {
		return;
	}
}

void config::import_cfg() {
	try {
		nlohmann::json config;
		std::string encoded = get_clipboard();
		std::string decoded = base64_decode(encoded);

		std::stringstream stream(decoded);
		stream >> config;
		varsFromJSON(config);
	}
	catch (...) {}
}

void config::export_cfg() {
	try {
		nlohmann::json config = varsToJSON();
		std::string decoded = config.dump();
		std::string encoded = base64_encode(decoded);
		set_clipboard(encoded);
	}
	catch (...) {}
}