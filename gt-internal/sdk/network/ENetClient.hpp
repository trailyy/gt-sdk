#pragma once
#include <cstdint>
#include <string>
#include "../proton/Boost.hpp"

#pragma pack(push, 1)
class ENetClient
{
public:
	virtual ~ENetClient(); // 0

	BoostSignal m_sig_unk1; // 8
	BoostSignal m_sig_unk2;
	BoostSignal m_sig_unk3;
	BoostSignal m_sig_unk4;
	char pad1[24]; // 72
	void* m_host; // 0xa0
	void* m_peer; // 0xa8
	uint32_t m_timed_out_timestamp;
	char pad2[12];
	std::string m_server_ip; // 0xc0
	uint32_t m_server_port; // 0xe0
	char pad3[4];
	int m_token; // 0xe8
	int m_user; // 0xec
	std::string m_door_id; // 0xf0
	int m_lmode; // 0x110
	char pad4[4];
	std::string m_uuid_token; // 0x118
};
#pragma pack(pop)