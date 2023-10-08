#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_SendPacket(int type, std::string& packet, void* peer)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_send_packet_fn)>(g_hooks->hkSendPacket.m_orig);

	orig(type, packet, peer);
}