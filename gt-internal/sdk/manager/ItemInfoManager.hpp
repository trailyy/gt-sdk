#pragma once
#include <cstdint>
#include <vector>
#include "../enums.hpp"

#pragma pack(push, 1)
class ItemInfo
{
public:
	uint32_t m_id;
	eItemType m_type;
	eMaterialType m_material;
	char pad1[4];
	std::string m_name;
	uint32_t m_texture_hash;
	char pad2[4];
	std::string m_texture_path;
	eVisualEffectType m_visual_effect;
	int m_cook_time;
	_Vector2<uint8_t> m_texture_pos;
	char pad3[2];
	eTileStorageType m_storage;
	uint32_t m_compute_value;
	eTileCollisionType m_collision;
	uint16_t m_hits_to_destroy;
	eItemFlags m_flags;
	char pad4[68];
	uint32_t m_heal_time;
	eBodyPart m_body_part;
	char m_seed_base;
	char m_seed_overlay;
	char m_tree_base;
	char m_tree_leaves;
	uint32_t m_seed_color;
	uint32_t m_seed_overlay_color;
	char pad5[4];
	uint32_t m_grow_time;
	char pad6[82];
	uint16_t m_rarity;
	char m_max_can_hold;
	char pad7[7];
	std::string m_extra_file;
	uint32_t m_extra_file_hash;
	uint32_t m_anim_ms;
	char pad8[40];
	uint32_t m_variant_item;
	char pad9[4];
	std::string m_pet_name;
	std::string m_pet_prefix;
	std::string m_pet_suffix;
	std::string m_pet_ability;
	char pad10[32];
	std::string m_unk_strs[8];
	char pad11[4];
	eItemFxFlags m_fx_flags;
	std::string m_extra_options;
	std::string m_extra_options2;
	std::string m_texture2_path;
	char pad12[64];

	struct extra_slots_t
	{
		uint32_t m_body_part1;
		uint32_t m_body_part2;
		uint32_t m_body_part3;
		uint32_t m_body_part4;
		uint32_t m_body_part5;
		uint32_t m_body_part6;
		uint32_t m_body_part7;
		uint32_t m_body_part8;
		uint32_t m_body_part9;
	} m_extra_slots;

	uint32_t m_extra_slot_count;
	std::string m_punch_parameters;
	char pad13[704];
};

class ItemInfoManager
{
public:
	virtual ~ItemInfoManager();

	std::vector<ItemInfo> m_items;
	char pad[24];

	ItemInfo* GetItem(uint32_t item_id)
	{
		if (item_id < m_items.size())
			return &m_items[item_id];

		return nullptr;
	}

	std::string GetItemName(uint32_t item_id)
	{
		if (ItemInfo* item = GetItem(item_id); item != nullptr)
			return item->m_name;

		return "[ invalid ]";
	}
};
#pragma pack(pop)