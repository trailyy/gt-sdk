#pragma once
#include "menu.hpp"
#include <Windows.h>
#include <d3d11.h>
#include "../globals.hpp"
#include "../hooks/render/renderer/renderer.hpp"

c_menu* g_menu = new c_menu();

bool c_menu::initialize(LPDIRECT3DDEVICE9 pDevice)
{
	if (m_initialized)
		return false;

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(g_globals->m_dll.m_window);
	ImGui_ImplDX9_Init(g_renderer->get_device());

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_NoMouseCursorChange;

	m_drawlist = ImGui::GetBackgroundDrawList();

	RECT window_size;
	GetWindowRect(g_globals->m_dll.m_window, &window_size);

	m_screen_size.x = window_size.right - window_size.left;
	m_screen_size.y = window_size.bottom - window_size.top;

	m_initialized = true;

	return true;
}

void c_menu::render()
{
	auto& io = ImGui::GetIO();
	io.MouseDrawCursor = m_open;

	if (!m_open)
		return;

	ImGui::Begin(_("gt-sdk"));
	{
		ImGui::Text(_("base address: 0x%llx"), g_globals->m_base_address);
		ImGui::Text(_("game logic component: 0x%llx"), (uintptr_t)g_sdk->get_game_logic());
	}
	ImGui::End();
}