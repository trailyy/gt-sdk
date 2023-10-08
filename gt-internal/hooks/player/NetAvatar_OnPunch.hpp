#include "../hooks.hpp"

void __cdecl Hooked_OnPunch(NetAvatar* net_avatar, Vector2 pos, NetAvatar* puncher)
{
	static auto orig = reinterpret_cast<decltype(g_sdk->m_on_punch_fn)>(g_hooks->hkOnPunch.m_orig);

	orig(net_avatar, pos, puncher);
}