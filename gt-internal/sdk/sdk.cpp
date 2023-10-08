#pragma once
#include "../globals.hpp"

c_sdk* g_sdk = new c_sdk();

c_module c_sdk::get_module() const
{
	return m_game_module;
}

void c_sdk::initialize()
{

	/*
	* themida/vmprotect hook NtProtectVirtualMemory
	* and various other functions that make it 
	* unable to use it properly, so here we restore 
	* or "unhook" one of the crucial ones
	*/

	// get handle to ntdll.dll
	c_module ntdll(_("ntdll.dll"));

	void* nt_protect_virtual_memory_fn = ntdll.get_proc_address(_("NtProtectVirtualMemory")).get();
	g_utils->write_memory(nt_protect_virtual_memory_fn, _("4C 8B D1 B8 50"));

	print(_("patched ntdll.dll!NtProtectVirtualMemory"));

	/*
	* todo - @trailyy:
	* make sure patterns are up
	* to date with each version
	* and make the patterns more 
	* unique
	*/

	// "get" type functions for core classes
	m_get_app_fn = m_game_module.find_pattern(_("E8 ? ? ? ? F3 0F 5C B0 ? ? ? ?"), _("GetApp"))
		.relative()
		.get<decltype(m_get_app_fn)>();
	m_get_base_app_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 48 8D 48 28"), _("GetBaseApp"))
		.relative()
		.get<decltype(m_get_base_app_fn)>();
	m_get_game_logic_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 44 8B A0 ? ? ? ?"), _("GetGameLogic"))
		.relative()
		.get<decltype(m_get_game_logic_fn)>();
	m_get_entity_root_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 48 8B C8 48 8D 54 24 ? E8 ? ? ? ? 48 8B F0 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 15 ? ? ? ?"), _("GetEntityRoot"))
		.relative()
		.get<decltype(m_get_entity_root_fn)>();
	m_get_enet_client_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 48 8B C8 4C 8D 4D B0"), _("GetClient"))
		.relative()
		.get<decltype(m_get_enet_client_fn)>();
	m_get_item_info_manager_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 8B 57 14"), _("GetItemInfoManager"))
		.relative()
		.get<decltype(m_get_item_info_manager_fn)>();
	m_get_resource_manager_fn = m_game_module.find_pattern(_("48 8D 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC 40 53 48 83 EC 20 8B D9"), _("GetResourceManager"))
		.get<decltype(m_get_resource_manager_fn)>();
	m_renderer_context = m_game_module.find_pattern(_("48 8B 05 ? ? ? ? 75 28"), _("RendererContext"))
		.to_absolute(3, 0)
		.get<decltype(m_renderer_context)>();

	/* Functions */

	// App
	m_app_update_fn = m_game_module.find_pattern(_("48 89 5C 24 ? 66 0F A4 E8 ?"), _("App::Update"))
		.get<decltype(m_app_update_fn)>();
	m_set_fps_limit_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 90 48 8D 4D F0 E8 ? ? ? ? 48 8B 4D 30"), _("BaseApp::SetFPSLimit"))
		.relative()
		.get<decltype(m_set_fps_limit_fn)>();
	m_log_msg_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 0F B6 6F 02"), _("LogMsg"))
		.relative()
		.get<decltype(m_log_msg_fn)>();

	// Component
	m_dialog_is_opened_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 84 C0 74 19 48 8B 03"), _("GameLogicComponent::DialogIsOpened"))
		.relative()
		.get<decltype(m_dialog_is_opened_fn)>();
	m_on_text_game_message_fn = m_game_module.find_pattern(_("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B FA"), _("GameLogicComponent::OnTextGameMessage"))
		.get<decltype(m_on_text_game_message_fn)>();
	m_process_tank_update_packet_fn = m_game_module.find_pattern(_("48 89 54 24 ? 0F B7 C3"), _("GameLogicComponent::ProcessTankUpdatePacket"))
		.get<decltype(m_process_tank_update_packet_fn)>();
	m_handle_touch_at_world_coordinates_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 20 5F C3 CC CC 40 53 48 83 EC 50"), _("LevelTouchComponent::HandleTouchAtWorldCoordinates"))
		.relative()
		.get<decltype(m_handle_touch_at_world_coordinates_fn)>();
	m_handle_track_packet_fn = m_game_module.find_pattern(_("E8 ? ? ? ? 90 48 8D 4D C0 E8 ? ? ? ? 49 8B CD"), _("TrackHandleComponent::HandleTrackPacket"))
		.relative()
		.get<decltype(m_handle_track_packet_fn)>();

	// Network
	m_send_packet_fn = m_game_module.find_pattern(_("E9 ? ? ? ? FB 78 46"), _("SendPacket"))
		.get<decltype(m_send_packet_fn)>();
	m_send_packet_raw_fn = m_game_module.find_pattern(_("E9 ? ? ? ? 64 79 C3"), _("SendPacketRaw"))
		.get<decltype(m_send_packet_raw_fn)>();

	if (m_get_base_app_fn && m_set_fps_limit_fn)
		m_set_fps_limit_fn(m_get_base_app_fn(), 0.0f);
}

App* c_sdk::get_app()
{
	App* app = m_get_app_fn();

	return app;
}

BaseApp* c_sdk::get_base_app()
{
	BaseApp* base_app = m_get_base_app_fn();

	return base_app;
}

GameLogicComponent* c_sdk::get_game_logic()
{
	GameLogicComponent* game_logic = m_get_game_logic_fn();

	return game_logic;
}

Entity* c_sdk::get_entity_root()
{
	Entity* entity_root = m_get_entity_root_fn();

	return entity_root;
}

ENetClient* c_sdk::get_enet_client()
{
	ENetClient* enet_client = m_get_enet_client_fn();

	return enet_client;
}

ItemInfoManager* c_sdk::get_item_info_manager()
{
	ItemInfoManager* item_info_manager = m_get_item_info_manager_fn();

	return item_info_manager;
}

ResourceManager* c_sdk::get_resource_manager()
{
	ResourceManager* resource_manager = m_get_resource_manager_fn();

	return resource_manager;
}

RendererContext* c_sdk::get_renderer_context()
{
	return *m_renderer_context;
}

void c_sdk::send_packet(eNetMessageType type, std::string& packet, void* peer)
{
	if (!m_send_packet_fn)
		return;

	m_send_packet_fn(type, packet, peer);
}

void c_sdk::send_packet_raw(eGamePacketType type, GameUpdatePacket* packet, int size, void* packet_sender, void* peer, int flags)
{
	if (!m_send_packet_raw_fn)
		return;

	m_send_packet_raw_fn(static_cast<int>(type), packet, size, packet_sender, peer, flags);
}

void c_sdk::process_tank_update_packet(GameLogicComponent* game_logic, GameUpdatePacket* packet)
{
	if (!m_get_game_logic_fn || !m_process_tank_update_packet_fn)
		return;

	m_process_tank_update_packet_fn(game_logic, packet);
}