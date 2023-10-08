#pragma once
#include <cstdint>
#include <list>

#pragma pack(push, 1)
struct InventoryItem
{
	uint16_t m_item_id;
	uint8_t m_count;
	uint8_t m_flags;
};

class PlayerItems
{
public:
	virtual ~PlayerItems();

	uint16_t m_clothes[12];
	std::list<InventoryItem> m_items; // 0x20
	uint16_t m_quick_slots[4];
	uint32_t m_backpack_size; // 0x38
	char pad1[4];
	std::list<InventoryItem> m_filtered_items; // 0x40
	char pad2[8];
	uint16_t m_selected_item; // 0x58
	char pad3[6];
	int m_gems; // 0x60
	char pad4[4];
	int m_gems_collected; // 0x70
	char pad5[20];
};
#pragma pack(pop)