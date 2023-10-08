#pragma once
#include "../hooks.hpp"

void __cdecl Hooked_HandleTrackPacket(TrackHandlerComponent* track_handler, const char* text)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_handle_track_packet_fn)>(g_hooks->hkDialogIsOpened.m_orig);

	orig(track_handler, text);
}