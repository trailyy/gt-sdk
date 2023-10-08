#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_Update(App* app)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_app_update_fn)>(g_hooks->hkUpdate.m_orig);

	// currently unused

	orig(app);
}