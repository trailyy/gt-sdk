#pragma once
#include <Windows.h>
#include <string>
#include <Psapi.h>

class c_address
{
public:
	template<typename T>
	c_address(T value)
	{
		m_value = (uintptr_t)value;
	}

	template <typename T = void*>
	T get()
	{
		return (T)(m_value);
	}

	template <typename T>
	void get(T& dest)
	{
		dest = get<T>();
	}

	c_address& add_offset(int offset)
	{
		if (m_value) m_value += offset;
		return *this;
	}

	c_address& to_absolute(int pre_offset, int post_offset)
	{
		if (m_value)
		{
			add_offset(pre_offset);
			m_value += sizeof(int) + *(int*)(m_value);
			add_offset(post_offset);
		}

		return *this;
	}

	c_address& relative()
	{
		if (*reinterpret_cast<std::uint8_t*>(m_value) != 0xE8)
			return *this;

		std::int32_t relative_address = *reinterpret_cast<std::int32_t*>(m_value + 1);
		m_value += relative_address + 5;

		return *this;
	}

	c_address& dereference(int amount = 1)
	{
		if (m_value) while (amount-- != 0) m_value = *(uintptr_t*)(m_value);
		return *this;
	}

	bool is_valid() { return m_value != 0; };

private:
	uintptr_t m_value;
};

class c_module
{
public:
	explicit c_module(const char* name) : m_name(name) { initialize(); };

	void initialize()
	{
		initialize_module();
		initialize_bounds();
	}

	c_address get_base_address();
	c_address get_proc_address(const char* proc_name);
	c_address find_pattern(std::string pattern, std::string name = "");

	bool is_loaded() const { return m_module != 0; };
	const char* get_name() const { return m_name; };

private:
	HMODULE m_module = NULL;
	uintptr_t m_start = 0;
	uintptr_t m_end = 0;
	const char* m_name = "";

	void initialize_module()
	{
		m_module = GetModuleHandleA(m_name);
	}

	void initialize_bounds()
	{
		if (!is_loaded())
			return;

		MODULEINFO mi;
		BOOL status = K32GetModuleInformation(GetCurrentProcess(), m_module, &mi, sizeof(mi));

		if (!status)
		{
			print("failed to initialize bounds for %s", m_name);
			return;
		}

		m_start = reinterpret_cast<uintptr_t>(m_module);
		m_end = m_start + static_cast<uintptr_t>(mi.SizeOfImage);
	}
};