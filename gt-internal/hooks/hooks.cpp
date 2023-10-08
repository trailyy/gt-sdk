#pragma once
#include "hooks.hpp"
#include "../globals.hpp"
#include "../utils/utils.hpp"

// hooks
#include "render/EndScene.hpp"
#include "render/WndProc.hpp"

#include "app/App_Update.hpp"
#include "app/BaseApp_SetFPSLimit.hpp"
#include "app/LogMsg.hpp"

#include "component/GameLogicComponent_DialogIsOpened.hpp"
#include "component/GameLogicComponent_OnTextGameMessage.hpp" // missing
#include "component/GameLogicComponent_ProcessTankUpdatePacket.hpp"
#include "component/LevelTouchComponent_HandleTouchAtWorldCoordinates.hpp"
#include "component/TrackHandlerComponent_HandleTrackPacket.hpp"

#include "network/SendPacket.hpp"
#include "network/SendPacketRaw.hpp"

#include "player/NetAvatar_CanMessageT4.hpp" // missing
#include "player/NetAvatar_OnPunch.hpp" // missing

#include "world/Tile_Serialize.hpp" // missing
#include "world/WorldCamera_CameraUpdate.hpp" // missing

c_hooks* g_hooks = new c_hooks();

void c_hooks::initialize()
{
	// initialize minhook... duh...
	MH_Initialize();

	// AppClass might be common, so lets search for both the window class and window name
	g_globals->m_dll.m_window = FindWindowA(_("AppClass"), _("Growtopia"));

	hkEndScene.hook(g_renderer->get_methods_table()[42], Hooked_EndScene);
	print(_("hooked endscene"));

	// hook our game functions
	hkUpdate.hook(g_sdk->m_app_update_fn, Hooked_Update);
	hkSetFPSLimit.hook(g_sdk->m_set_fps_limit_fn, Hooked_SetFPSLimit);
	hkLogMsg.hook(g_sdk->m_log_msg_fn, Hooked_LogMsg);

	hkDialogIsOpened.hook(g_sdk->m_dialog_is_opened_fn, Hooked_DialogIsOpened);
	hkOnTextGameMessage.hook(g_sdk->m_on_text_game_message_fn, Hooked_OnTextGameMessage);
	hkProcessTankUpdatePacket.hook(g_sdk->m_process_tank_update_packet_fn, Hooked_ProcessTankUpdatePacket);
	hkHandleTouchAtWorldCoordinates.hook(g_sdk->m_handle_touch_at_world_coordinates_fn, Hooked_HandleTouchAtWorldCoordinates);
	hkHandleTrackPacket.hook(g_sdk->m_handle_track_packet_fn, Hooked_HandleTrackPacket);

	// "hook" wndproc
	g_globals->m_dll.m_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(g_globals->m_dll.m_window, GWLP_WNDPROC, (LONG_PTR)Hooked_WndProc));

	print(_("hooked everything =)"));
}

void c_hooks::shutdown()
{
	// restore the wndproc to the original one
	SetWindowLongPtrA(g_globals->m_dll.m_window, GWLP_WNDPROC, (LONG_PTR)g_globals->m_dll.m_wndproc);

	hkEndScene.clear();

	hkUpdate.clear();
	hkSetFPSLimit.clear();
	hkLogMsg.clear();

	hkDialogIsOpened.clear();
	hkOnTextGameMessage.clear();
	hkProcessTankUpdatePacket.clear();
	hkHandleTouchAtWorldCoordinates.clear();
	hkHandleTrackPacket.clear();	

	g_renderer->shutdown();

	// cleanup
	auto ctx = ImGui::GetCurrentContext();
	if (ctx)
	{
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	// do i even have to comment this
	MH_Uninitialize();

	print(_("unhooked everything =(\n"));
}