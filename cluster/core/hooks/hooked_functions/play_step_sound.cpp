#include "../hooks.h"

void __fastcall c_hooks::c_play_step_sound::hook(REGISTERS, vector3_t& origin, void* surface, float volume, bool force) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, origin, surface, volume, force);

	original(ecx, edx, origin, surface, volume, force);
}
