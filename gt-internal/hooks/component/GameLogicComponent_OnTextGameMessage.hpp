#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_OnTextGameMessage(GameLogicComponent* game_logic, const char* packet)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_on_text_game_message_fn)>(g_hooks->hkOnTextGameMessage.m_orig);

	return orig(game_logic, packet);
}