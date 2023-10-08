#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_HandleTouchAtWorldCoordinates(LevelTouchComponent* level_touch, Vector2 pos, bool unk)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_handle_touch_at_world_coordinates_fn)>(g_hooks->hkHandleTouchAtWorldCoordinates.m_orig);

	// currently unused

	orig(level_touch, pos, unk);
}