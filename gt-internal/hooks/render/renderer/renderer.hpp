#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3d11.h>
#include <dxgi.h>
#include <stdio.h>
#include <stdint.h>

class c_renderer
{
public:
	void initialize();
	void shutdown();

	uint64_t* get_methods_table() const { return m_methods_table; }

	IDirect3DDevice9* get_device() { return m_device; }
	void set_device(IDirect3DDevice9* device) { m_device = device; }
private:
	IDirect3DDevice9* m_device = NULL;
	uint64_t* m_methods_table = NULL;
};

extern c_renderer* g_renderer;