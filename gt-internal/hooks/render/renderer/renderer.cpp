#pragma once
#include "renderer.hpp"
#include "../../../globals.hpp"
#include "../../../utils/utils.hpp"

c_renderer* g_renderer = new c_renderer();

#define RELEASE_D3D(p) if(p) { p->Release(); p = nullptr; }

void c_renderer::initialize()
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = _("bozowindow");
	windowClass.hIconSm = NULL;

	RegisterClassExA(&windowClass);

	HWND window = CreateWindowExA(NULL, windowClass.lpszClassName, _("bozowindow1337"), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

	print(_("created dummy window"));

	HMODULE d3d9_dll = GetModuleHandleA(_("d3d9.dll"));
	if (!d3d9_dll)
	{
		print("failed to find d3d9.dll");

		DestroyWindow(window);
		UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);

		return;
	}

	void* Direct3DCreate9 = GetProcAddress(d3d9_dll, "Direct3DCreate9");
	if (!Direct3DCreate9)
	{
		print("failed to find Direct3DCreate9");

		DestroyWindow(window);
		UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);

		return;
	}

	LPDIRECT3D9 Direct3D9 = ((LPDIRECT3D9(__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION);
	if (!Direct3D9)
	{
		print("failed to init Direct3DCreate9");

		DestroyWindow(window);
		UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);

		return;
	}

	D3DPRESENT_PARAMETERS params;
	params.BackBufferWidth = 0;
	params.BackBufferHeight = 0;
	params.BackBufferFormat = D3DFMT_UNKNOWN;
	params.BackBufferCount = 0;
	params.MultiSampleType = D3DMULTISAMPLE_NONE;
	params.MultiSampleQuality = NULL;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	params.Windowed = 1;
	params.EnableAutoDepthStencil = 0;
	params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	params.Flags = NULL;
	params.FullScreen_RefreshRateInHz = 0;
	params.PresentationInterval = 0;

	LPDIRECT3DDEVICE9 Direct3DDevice9;
	if (Direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &Direct3DDevice9) < 0)
	{
		print("failed to CreateDevice");

		Direct3DDevice9->Release();

		DestroyWindow(window);
		UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);

		return;
	}

	print(_("created device"));

	m_methods_table = (uint64_t*)::calloc(119, sizeof(uint64_t));
	memcpy(m_methods_table, *(uint64_t**)Direct3DDevice9, 119 * sizeof(uint64_t));

	print(_("copied vtable"));

	RELEASE_D3D(Direct3DDevice9);
	RELEASE_D3D(Direct3D9);

	print(_("initialized renderer"));

	DestroyWindow(window);
	UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
}

void c_renderer::shutdown()
{
	free(m_methods_table);
	m_methods_table = NULL;
}