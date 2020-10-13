#include "../hooks.h"

bool __fastcall c_hooks::c_should_skip_animation_frame::hook(REGISTERS) {
	if (g_hooks.is_unhooking || !ecx)
		return original(ecx, edx);

	return false;
}
