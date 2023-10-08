#pragma once

#pragma pack(push, 1)
class EncryptedFloat
{
public:
	inline float get() const
	{
		return m_encrypted1 - m_weight * 0.5f;
	}

	inline void set(float value)
	{
		m_encrypted1 = value + (m_weight * 0.5f);
		m_encrypted2 = value + m_weight;
	}

private:
	float m_encrypted1;
	char pad[4];
	float m_encrypted2;
	float m_weight;
};
#pragma pack(pop)