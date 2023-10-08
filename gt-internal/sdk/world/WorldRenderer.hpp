#pragma once
#include <cstdint>
#include "WorldCamera.hpp"

class World;

#pragma pack(push, 1)
class WorldRenderer
{
public:
	virtual ~WorldRenderer();

	World* world;
	char pad1[136];
	WorldCamera* camera;
};
#pragma pack(pop)