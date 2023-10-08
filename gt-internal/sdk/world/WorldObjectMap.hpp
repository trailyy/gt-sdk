#pragma once
#include <list>
#include "../proton/Vector.hpp"

#pragma pack(push, 1)
class WorldObject
{
public:
    virtual ~WorldObject();

    Vector2 m_pos;
    uint16_t m_item_id;
    uint8_t m_count;
    uint8_t m_flags;
    uint32_t m_object_id;
    uint32_t m_insert_timestamp;
    char pad1[20];
};
static_assert(sizeof(WorldObject) == 0x30);

class WorldObjectMap
{
public:
    virtual ~WorldObjectMap();

    char pad1[72];
    std::list<WorldObject> m_objects;
};
#pragma pack(pop)