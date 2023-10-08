#pragma once
#include "../hooks.hpp"
#include "renderer/renderer.hpp"
#include "../../menu/menu.hpp"
#include "../../lib/imgui/imgui.h"
#include "../../lib/imgui/imgui_impl_dx9.h"
#include "../../lib/imgui/imgui_impl_win32.h"

using endscene_t = HRESULT(WINAPI*)(IDirect3DDevice9*);
HRESULT WINAPI Hooked_EndScene(IDirect3DDevice9* device)
{
	static auto orig = (endscene_t)g_hooks->hkEndScene.m_orig;

	if (!g_menu->initialize(device) && g_menu->m_initialized == false)
		return orig(device);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	g_menu->render();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return orig(device);
}