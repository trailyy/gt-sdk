#pragma once
#include <cstdint>
#include "../proton/Vector.hpp"
#include "../enums.hpp"

#pragma pack(push, 1)
struct GameUpdatePacket
{
	eGamePacketType m_type;
	uint8_t m_byte1;
	uint8_t m_byte2;
	uint8_t m_byte3;
	int m_int1;
	int m_int2;
	int m_flags;
	float m_float_data;
	int m_int_data;
	Vector2 m_vec1;
	Vector2 m_vec2;
	float m_float;
	_Vector2<int> m_vec_int;
	uint32_t m_extended_data_size;

	inline std::uint8_t* get_extended_data()
	{
		return reinterpret_cast<std::uint8_t*>(this) + sizeof(GameUpdatePacket);
	}
};
#pragma pack(pop)

static_assert(sizeof(GameUpdatePacket) == 56);