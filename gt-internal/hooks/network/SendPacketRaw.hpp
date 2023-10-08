#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_SendPacketRaw(int type, GameUpdatePacket* packet, int size, void* packet_sender, void* enet_peer, int flag)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_send_packet_raw_fn)>(g_hooks->hkSendPacketRaw.m_orig);

	orig(type, packet, size, packet_sender, enet_peer, flag);
}