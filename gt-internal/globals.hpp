#pragma once
#include "sdk/sdk.hpp"
#include "lib/xorstr/xorstr.hpp"

class c_globals
{
public:
	struct dll_data_t
	{
		HMODULE m_self;
		HWND m_window;
		WNDPROC m_wndproc;
		bool m_unload;
	} m_dll;

	uintptr_t m_base_address;
};

extern c_globals* g_globals;