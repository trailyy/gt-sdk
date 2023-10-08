#pragma once
#include "BaseApp.hpp"
#include "../component/GameLogicComponent.hpp"
#include "../component/TrackHandlerComponent.hpp"
#include "../manager/ItemInfoManager.hpp"
#include "../manager/TileSheetManager.hpp"
#include "../manager/PlayerTributeManager.hpp"
#include "../variant/VariantDB.hpp"

#pragma pack(push, 1)
class App : public BaseApp
{
public:
	char pad[64];
	GameLogicComponent* m_game_logic_component;
	TrackHandlerComponent* m_track_handler_component;
	ItemInfoManager* m_item_info_manager;
	TileSheetManager m_tile_sheet_manager;
	PlayerTributeManager* m_player_tribute_manager;
	char pad1[1136];
	VariantDB m_variant_db;

	Variant* GetVariant(const std::string& name)
	{
		return m_variant_db.GetVariant(name);
	}

	FunctionObject* GetFunction(const std::string& name)
	{
		return m_variant_db.GetFunction(name);
	}
};
#pragma pack(pop)