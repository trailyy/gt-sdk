#pragma once
#include <algorithm>

class Color
{
public:
	Color() : m_colors() { };

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : m_colors()
	{
		m_colors[0] = r;
		m_colors[1] = g;
		m_colors[2] = b;
		m_colors[3] = a;
	};

	Color(float r, float g, float b, float a = 255) : m_colors()
	{
		m_colors[0] = r * 255;
		m_colors[0] = g * 255;
		m_colors[0] = b * 255;
		m_colors[0] = a * 255;
	}

	unsigned char& operator[](int idx)
	{
		return m_colors[idx];
	}

	uint32_t AsHex(bool alpha = true)
	{
		int a = alpha ? m_colors[3] : 255;
		uint8_t ret[4] = { m_colors[0], m_colors[1], m_colors[2], a };

		return uint32_t(ret);
	}

	int AsGt(bool alpha = true)
	{
		int a = alpha ? m_colors[3] : 255;
		int ret = ((m_colors[0] << 8) + (m_colors[1] << 16) + (m_colors[2] << 24) + a);

		return ret;
	}

private:
	uint8_t m_colors[4];
};