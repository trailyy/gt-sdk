#pragma once
#include <cstdint>
#include <deque>
#include <string>
#include "Boost.hpp"

#pragma pack(push, 1)
class Console
{
public:
	virtual ~Console();

	BoostSignal m_sig_on_text_added;
	uint32_t m_max_lines;
	std::deque<std::string> m_stream;
	char pad[84];
};
#pragma pack(pop)