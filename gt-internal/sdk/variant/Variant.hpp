#pragma once
#include <cstdint>
#include <string>
#include "../proton/Vector.hpp"
#include "../enums.hpp"
#include "../../utils/utils.hpp"

class Entity;
class EntityComponent;

#pragma pack(push, 1)
class Variant
{
public:
	Variant() = default;

	eVariantType GetType() const { return m_type; }
	float GetFloat() const { return m_float_value; }
	std::string GetString() const { return m_string_value; }
	Vector2 GetVec2() const { return m_vec2_value; }
	Vector GetVec3() const { return m_vec3_value; }
	uint32_t GetUInt() const { return m_uint_value; }
	Entity* GetEntity() const { return static_cast<Entity*>(m_ptr); }
	EntityComponent* GetComponent() const { return static_cast<EntityComponent*>(m_ptr); }
	Vector4 GetVec4() const { return m_vec4_value; }
	int32_t GetInt() const { return m_int_value; }

	void Set(float value)
	{
		m_float_value = value;
		m_type = eVariantType::FLOAT;
	}

	void Set(const std::string& value)
	{
		m_string_value = value;
		m_type = eVariantType::STRING;
	}

	void Set(Vector2 value)
	{
		m_vec2_value = value;
		m_type = eVariantType::VECTOR2;
	}

	void Set(Vector value)
	{
		m_vec3_value = value;
		m_type = eVariantType::VECTOR3;
	}

	void Set(std::uint32_t value)
	{
		m_uint_value = value;
		m_type = eVariantType::UINT32;
	}

	void Set(Entity* value)
	{
		m_ptr = static_cast<void*>(value);
		m_type = eVariantType::ENTITY;
	}

	void Set(EntityComponent* value)
	{
		m_ptr = static_cast<void*>(value);
		m_type = eVariantType::COMPONENT;
	}

	void Set(Vector4 value)
	{
		m_vec4_value = value;
		m_type = eVariantType::RECT;
	}

	void Set(std::int32_t value)
	{
		m_int_value = value;
		m_type = eVariantType::INT32;
	}

	void operator=(float value) { Set(value); }
	void operator=(const std::string& value) { Set(value); }
	void operator=(Vector2 value) { Set(value); }
	void operator=(Vector value) { Set(value); }
	void operator=(std::uint32_t value) { Set(value); }
	void operator=(Entity* value) { Set(value); }
	void operator=(EntityComponent* value) { Set(value); }
	void operator=(Vector4 value) { Set(value); }
	void operator=(std::int32_t value) { Set(value); }

	eVariantType m_type;
	char pad[7];
	void* m_ptr;

	union
	{
		uint8_t m_value[16];
		float m_float_value;
		Vector2 m_vec2_value;
		Vector m_vec3_value;
		uint32_t m_uint_value;
		Vector4 m_vec4_value;
		int m_int_value;
	};

	std::string m_string_value;
	BoostTrackableSignal m_sig_on_changed;

	friend class VariantList;
};

class VariantList
{
public:
	VariantList() = default;
	explicit VariantList(std::uint8_t* data) { SerializeFromMem(data); }

	void SerializeFromMem(std::uint8_t* data)
	{
		using enum eVariantType;

		std::uint8_t count;
		g_utils->read(count, data);

		for (std::uint8_t i = 0; i < count; ++i)
		{
			std::uint8_t index;
			g_utils->read(index, data);

			Variant& var = m_variants[index];
			g_utils->read(var.m_type, data);

			switch (var.m_type)
			{
				case eVariantType::FLOAT:
					g_utils->read(var.m_float_value, data);
					break;

				case eVariantType::STRING:
					g_utils->read_string(var.m_string_value, data);
					break;

				case eVariantType::VECTOR2:
					g_utils->read(var.m_vec2_value, data);
					break;

				case eVariantType::VECTOR3:
					g_utils->read(var.m_vec3_value, data);
					break;

				case eVariantType::UINT32:
					g_utils->read(var.m_uint_value, data);
					break;

				case eVariantType::INT32:
					g_utils->read(var.m_int_value, data);
					break;

				default:
					break;
			}
		}
	}

	std::uint8_t* SerializeToMem(std::uint32_t* data_size) const
	{
		std::uint8_t variant_count = 0;
		*data_size = 1;

		for (std::uint8_t i = 0; i < 7; ++i)
		{
			const Variant& var = m_variants[i];

			if (var.m_type == eVariantType::UNUSED)
				break;

			variant_count++;
			*data_size += 2;

			switch (var.m_type)
			{
				case eVariantType::FLOAT:
					*data_size += sizeof(float);
					break;

				case eVariantType::STRING:
					*data_size += static_cast<uint32_t>(sizeof(uint32_t) + var.m_string_value.size());
					break;

				case eVariantType::VECTOR2:
					*data_size += sizeof(Vector2);
					break;

				case eVariantType::VECTOR3:
					*data_size += sizeof(Vector);
					break;

				case eVariantType::UINT32:
					*data_size += sizeof(uint32_t);
					break;

				case eVariantType::INT32:
					*data_size += sizeof(int32_t);
					break;

				default:
					break;
			}
		}

		std::uint8_t* data = new std::uint8_t[*data_size];
		std::uint8_t* data_start = data;

		g_utils->write(variant_count, data);

		for (std::uint8_t i = 0; i < variant_count; ++i)
		{
			const Variant& var = m_variants[i];

			g_utils->write(i, data);
			g_utils->write(var.m_type, data);

			switch (var.m_type)
			{
				case eVariantType::FLOAT:
					g_utils->write(var.m_float_value, data);
					break;

				case eVariantType::STRING:
					g_utils->write_string(var.m_string_value, data);
					break;

				case eVariantType::VECTOR2:
					g_utils->write(var.m_vec2_value, data);
					break;

				case eVariantType::VECTOR3:
					g_utils->write(var.m_vec3_value, data);
					break;

				case eVariantType::UINT32:
					g_utils->write(var.m_uint_value, data);
					break;

				case eVariantType::INT32:
					g_utils->write(var.m_int_value, data);
					break;

				default:
					break;
			}
		}

		return data_start;
	}

	inline Variant& Get(std::size_t index) { return m_variants[index]; }
	inline const Variant& Get(std::size_t index) const { return m_variants[index]; }

	inline Variant& operator[](std::size_t index) { return m_variants[index]; }
	inline const Variant& operator[](std::size_t index) const { return m_variants[index]; }

	Variant m_variants[7] = { };
};
#pragma pack(pop)