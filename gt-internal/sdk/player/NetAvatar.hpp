#pragma once
#include <cstdint>
#include <memory>
#include "../proton/Vector.hpp"
#include "../proton/EncryptedFloat.hpp"
#include "../enums.hpp"

#pragma pack(push, 1)
class NetAvatar
{
public:
	virtual ~NetAvatar(); // 0

	Vector2 m_pos; // 8
	Vector2 m_size; // 16 
	Vector2 m_encrypted_pos; // 24
	Vector2 m_encrypted_size; // 32
	std::string m_name; // 40
	int m_net_id; // 72 
	char pad1[21]; // 76
	bool m_facing_left; // 97
	char pad2[102]; // 98
	float m_jump_state; // 200
	int m_unk_int; // 204
	_Vector2<int> m_tile; // 208
	int m_is_tile_solid; // 216
	bool m_can_jump; // 220
	bool m_is_sliding; // 221 
	char pad3[6]; // 222
	_Vector2<EncryptedFloat> m_velocity; // 228
	char pad4[48]; // 260
	ePlayerFlags m_flags; // 308
	uint32_t m_freeze_state; // 312
	int m_user_id;
	char pad5[16];
	std::string m_country;
	char pad6[8];
	bool m_is_invis;
	bool m_is_mod;
	bool m_is_smod;
	char pad7[9];
	uint32_t m_bubble_state;
	uint32_t m_state;
	char pad8[20];
	bool m_down_key_state;
	char pad9[4];
	uint32_t m_punch_effect;
	char pad10[28];
	EncryptedFloat m_gravity;
	EncryptedFloat m_acceleration;
	EncryptedFloat m_speed;
	float m_water_speed;

	_Vector2<int> GetTilePos() const
	{
		return
		{
			static_cast<int32_t>((m_pos.x + m_size.x / 2.f) / 32.f),
			static_cast<int32_t>((m_pos.y + m_size.y / 2.f) / 32.f)
		};
	}

	void SetPosAtTile(_Vector2<int> tile_pos)
	{
		m_pos.x = static_cast<float>(tile_pos.x) * 32.f + 6.f;
		m_pos.y = static_cast<float>(tile_pos.y) * 32.f + 2.f;
	}
};
#pragma pack(pop)