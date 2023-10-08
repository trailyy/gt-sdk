#pragma once
#include "../../globals.hpp"
#include "../../lib/imgui/imgui_impl_win32.h"
#include "../../menu/menu.hpp"
#include "../hooks.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT Hooked_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_KEYDOWN && wparam == VK_INSERT)
		g_menu->m_open = !g_menu->m_open;

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	return CallWindowProcA(g_globals->m_dll.m_wndproc, hwnd, msg, wparam, lparam);
}