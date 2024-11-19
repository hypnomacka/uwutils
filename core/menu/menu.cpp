#include <pch.h>
#include "menu.hpp"
#include "../features/features.hpp"
#include "../../dependencies/imgui/fx.inl"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Render menu
void menu::render() {
	// Set menu size
	gui::SetWindowSize({ 400, 400 });
	gui::SetNextWindowSizeConstraints({ 400, 400 }, { 900, 900 });
	// Begin imgui
	gui::Begin(xorstr("UwU"), &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	// Menu variables
	ImVec2 pos = gui::GetWindowPos();
	float width = gui::GetWindowWidth();
	float height = gui::GetWindowHeight();

	// Render title background
	gui::GetWindowDrawList()->AddRectFilled({ pos.x, pos.y }, { pos.x + width, pos.y + 36 }, gui::GetColorU32(ImGuiCol_TitleBg), 8.f, ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight);
	// Render title border
	gui::GetWindowDrawList()->AddRectFilled({ pos.x, pos.y + 35 }, { pos.x + width, pos.y + 36 }, gui::GetColorU32(ImGuiCol_Border));

	// Render cheat name
	gui::PushFont(title);
	gui::GetWindowDrawList()->AddText(ImVec2(pos.x + 11, pos.y + 10), ImColor(var::menu::accent), xorstr("Uwu"));
	gui::GetWindowDrawList()->AddText(ImVec2(pos.x + 48, pos.y + 10), ImColor(190, 190, 190, 255), xorstr("tils"));
	gui::PopFont();

	// Render tabs
	static auto active_tab = 0;
	gui::SetCursorPos({ width - 114, 0 });
	if (gui::CustomTab(ICON_FA_EYE, active_tab == 0))
		active_tab = 0;

	gui::SameLine(0, 0);
	if (gui::CustomTab(ICON_FA_USER, active_tab == 1))
		active_tab = 1;

	gui::SameLine(0, 0);
	if (gui::CustomTab(ICON_FA_FOLDER, active_tab == 2))
		active_tab = 2;

	// Groups
	auto group_size = ImVec2(width / 2 - 13, height - 53);
	gui::SetCursorPos({ 9,44 });
	switch (active_tab) {
		case 0: 
			gui::BeginChild(xorstr("visual"), group_size, true, ImGuiWindowFlags_MenuBar); {
				menu::tabs::visual();
			}
			gui::EndChild();
			gui::SameLine();
			gui::BeginChild(xorstr("misc"), group_size, true, ImGuiWindowFlags_MenuBar); {
				menu::tabs::misc();
			}
			gui::EndChild();
		break;
		case 1: 
			gui::BeginChild(xorstr("troll"), group_size, true, ImGuiWindowFlags_MenuBar); {
				menu::tabs::troll();
			}
			gui::EndChild();
			gui::SameLine();
			gui::BeginChild(xorstr("Skin changer"), group_size, true, ImGuiWindowFlags_MenuBar); {
				menu::tabs::skins();
			}
			gui::EndChild();
		break;
		case 2:	
			gui::BeginChild(xorstr("config"), group_size, true, ImGuiWindowFlags_MenuBar); {
				menu::tabs::config();
			}
			gui::EndChild();
			gui::SameLine();
			gui::BeginChild(xorstr("extra"), group_size, true, ImGuiWindowFlags_MenuBar); {
				menu::tabs::config_extra();
			}
			gui::EndChild();
		break;
	}

	// Background
	if (var::menu::background) 
		gui::GetBackgroundDrawList()->AddRectFilled({ 0, 0 }, gui::GetIO().DisplaySize, ImColor(var::menu::background_color));
	if (var::menu::background_effect) 
		FX(gui::GetBackgroundDrawList(), { 0, 0 }, gui::GetIO().DisplaySize, gui::GetTime());
	
	// End imgui
	gui::End();
}

bool menu::initialize(IDirect3DDevice9* device) {
	window = FindWindowW((L"Valve001"), NULL);
	if (!window) throw std::runtime_error(xorstr("failed to initialize window"));
	original_process = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));

	gui::CreateContext();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);

	// Set style colors
	gui::StyleColors();
	// Create imgui fonts
	gui::GetIO().FontDefault = gui::GetIO().Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\calibri.ttf"), 12.f, nullptr);
	defaultfont = gui::GetIO().Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\calibri.ttf"), 12.0f, nullptr);
	title = gui::GetIO().Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\calibrib.ttf"), 19.0f, nullptr);
	group = gui::GetIO().Fonts->AddFontFromFileTTF(xorstr("C:\\Windows\\Fonts\\calibrib.ttf"), 13.0f, nullptr);
	static const ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
	icons = gui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 20.0f, 0, ranges);

	console::log(xorstr("menu initialized\n"));
	initialized = true;
	return true;
}

void menu::release() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	gui::DestroyContext();
	SetWindowLongW(FindWindowW((L"Valve001"), NULL), GWL_WNDPROC, reinterpret_cast<LONG>(original_process));
}

LRESULT WINAPI menu::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_KEYUP && wparam == var::menu::keybind)
		opened = !opened;

	if (opened && ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) return true;

	return CallWindowProc(original_process, hwnd, msg, wparam, lparam);
}