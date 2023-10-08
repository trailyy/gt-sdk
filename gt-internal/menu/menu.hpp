#pragma once
#include "../globals.hpp"
#include <d3d9.h>
#include <d3dx9.h>
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/imgui_impl_dx9.h"
#include "../lib/imgui/imgui_impl_win32.h"

class c_menu
{
public:
	bool m_initialized = false;
	bool m_open = true;
	ImVec2 m_screen_size = { };

	ImDrawList* m_drawlist = nullptr;

	bool initialize(LPDIRECT3DDEVICE9 device);
	void render();
};

extern c_menu* g_menu;