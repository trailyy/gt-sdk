#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "../enums.hpp"

#pragma pack(push, 1)
class TileExtra
{
public:
	virtual ~TileExtra();

	eTileExtraType m_type;
	char pad1[3];

	union
	{
		int m_item_price;
		uint32_t m_lock_owner;
	};

	char pad2[32];
	std::string m_label;
	char pad3[32];

	union
	{
		uint32_t m_item_id;
		uint32_t m_last_update;
	};

	uint32_t m_growth;
	char m_fruit_count;
	char pad4[31];
	std::vector<uint32_t> m_access_list;
};
#pragma pack(pop)