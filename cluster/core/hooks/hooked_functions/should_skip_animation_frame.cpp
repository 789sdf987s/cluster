#include "../hooks.h"

bool __fastcall c_hooks::c_should_skip_animation_frame::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	return original(ecx, edx);
}
