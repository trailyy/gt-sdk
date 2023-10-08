#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_ProcessTankUpdatePacket(GameLogicComponent* game_logic, GameUpdatePacket* packet)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_process_tank_update_packet_fn)>(g_hooks->hkProcessTankUpdatePacket.m_orig);

	orig(game_logic, packet);
}