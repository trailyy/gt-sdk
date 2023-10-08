#pragma once

#define nullcheck(x) if (x == nullptr) return;
#define nullcheckc(x) if (x == nullptr) continue;
#define nullcheckb(x) if (x == nullptr) break;

#include <set>
#include <string>
#include <vector>
#include <locale>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <Windows.h>
#include <thread>

#include "app/App.hpp"
#include "app/Entity.hpp"
#include "component/EntityComponent.hpp"
#include "network/ENetClient.hpp"
#include "network/GameUpdatePacket.hpp"
#include "component/GameLogicComponent.hpp"
#include "component/TrackHandlerComponent.hpp"
#include "component/LevelTouchComponent.hpp"
#include "manager/ItemInfoManager.hpp"
#include "player/AvatarData.hpp"
#include "player/AvatarRenderData.hpp"
#include "player/NetAvatar.hpp"
#include "world/WorldTileMap.hpp"
#include "proton/Vector.hpp"
#include "variant/Variant.hpp"
#include "render/RendererContext.hpp"
#include "render/Surface.hpp"
#include "../utils/module.hpp"
#include "enums.hpp"

class c_sdk
{
public:
	void(__cdecl* m_app_update_fn)(App*) = NULL;
	void(__cdecl* m_set_fps_limit_fn)(BaseApp*, float) = NULL;
	void(__cdecl* m_log_msg_fn)(const char*, ...) = NULL;

	bool(__cdecl* m_dialog_is_opened_fn)() = NULL;
	void(__cdecl* m_on_text_game_message_fn)(GameLogicComponent*, const char*) = NULL;
	void(__cdecl* m_process_tank_update_packet_fn)(GameLogicComponent*, GameUpdatePacket*) = NULL;
	void(__cdecl* m_handle_touch_at_world_coordinates_fn)(LevelTouchComponent*, Vector2, bool) = NULL;
	void(__cdecl* m_handle_track_packet_fn)(TrackHandlerComponent*, const char*) = NULL;

	void(__cdecl* m_send_packet_fn)(int, std::string&, void*) = NULL;
	void(__cdecl* m_send_packet_raw_fn)(int, GameUpdatePacket*, int, void*, void*, int) = NULL;

	bool(__cdecl* m_can_message_t4_fn)(NetAvatar*) = NULL;
	void(__cdecl* m_get_visual_state_fn)(NetAvatar*, GameUpdatePacket*) = NULL;
	void(__cdecl* m_on_punch_fn)(NetAvatar*, Vector2, NetAvatar*) = NULL;

	void(__cdecl* m_serialize_fn)(TileExtra*, uint8_t*, uint32_t*, bool, World*, bool, Tile*, int) = NULL;
	void(__cdecl* m_camera_update_fn)(WorldCamera*, Vector2, Vector2) = NULL;

	void initialize();
	c_module get_module() const;

	App* get_app();
	BaseApp* get_base_app();
	GameLogicComponent* get_game_logic();
	Entity* get_entity_root();
	ENetClient* get_enet_client();
	ItemInfoManager* get_item_info_manager();
	ResourceManager* get_resource_manager();
	RendererContext* get_renderer_context();

	void send_packet(eNetMessageType, std::string&, void*);
	void send_packet_raw(eGamePacketType, GameUpdatePacket*, int, void*, void*, int);
	void process_tank_update_packet(GameLogicComponent*, GameUpdatePacket*);

private:
	c_module m_game_module = c_module(NULL);
	App* (__cdecl* m_get_app_fn)() = NULL;
	BaseApp* (__cdecl* m_get_base_app_fn)() = NULL;
	GameLogicComponent* (__cdecl* m_get_game_logic_fn)() = NULL;
	Entity* (__cdecl* m_get_entity_root_fn)() = NULL;
	ENetClient* (__cdecl* m_get_enet_client_fn)() = NULL;
	ItemInfoManager* (__cdecl* m_get_item_info_manager_fn)() = NULL;
	ResourceManager* (__cdecl* m_get_resource_manager_fn)() = NULL;
	RendererContext** m_renderer_context = NULL;
};

extern c_sdk* g_sdk;