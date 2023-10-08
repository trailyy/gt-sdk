#pragma once
#include <cstdint>
#include <d3d9.h>

// straight from bgfx
#define BGFX_CONFIG_MAX_TEXTURES 4096

#pragma pack(push, 1)
struct TextureD3D9
{
	union
	{
		IDirect3DBaseTexture9* m_ptr;
		IDirect3DTexture9* m_texture2d;
		IDirect3DVolumeTexture9* m_texture3d;
		IDirect3DCubeTexture9* m_texture_cube;
	};

	IDirect3DSurface9* m_surface;

	union
	{
		IDirect3DBaseTexture9* m_staging;
		IDirect3DTexture9* m_staging2d;
		IDirect3DVolumeTexture9* m_staging3d;
		IDirect3DCubeTexture9* m_staging_cube;
	};

	uint64_t m_flags;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_depth;
	uint8_t m_num_mips;
	uint8_t m_type;
	uint8_t m_requested_format;
	uint8_t m_texture_format;
};

class RendererContext
{
public:
	char pad1[312];
	IDirect3D9Ex* m_d3d9_ex;
	IDirect3DDevice9Ex* m_device_ex;
	IDirect3D9* m_d3d9;
	IDirect3DDevice9* m_device;
	char pad2[423592];
	TextureD3D9 m_textures[BGFX_CONFIG_MAX_TEXTURES];

	TextureD3D9 GetTexture(int id)
	{
		if (id > BGFX_CONFIG_MAX_TEXTURES - 1) return m_textures[BGFX_CONFIG_MAX_TEXTURES - 1];

		return m_textures[id];
	}
};
#pragma pack(pop)