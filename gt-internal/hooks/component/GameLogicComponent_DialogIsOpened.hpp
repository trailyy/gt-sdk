#pragma once
#include "../hooks.hpp"

bool __cdecl Hooked_DialogIsOpened()
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_dialog_is_opened_fn)>(g_hooks->hkDialogIsOpened.m_orig);

	return orig();
}