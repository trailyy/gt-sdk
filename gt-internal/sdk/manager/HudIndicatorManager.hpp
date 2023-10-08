#pragma once
#include <cstdint>

#pragma pack(push, 1)
class HudIndicatorManager
{
public:
	virtual ~HudIndicatorManager();

	char pad[24];
};
#pragma pack(pop)