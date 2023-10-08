#pragma once
#include <cstdint>
#include <string>

#include "WorldTileMap.hpp"
#include "WorldObjectMap.hpp"

#pragma pack(push, 1)
class World
{
public:
	virtual ~World();

	char pad1[2];
	uint16_t m_version;
	char pad2[132];
	WorldTileMap m_tile_map;
	WorldObjectMap m_object_map;
	std::string m_name;
};
#pragma pack(pop)