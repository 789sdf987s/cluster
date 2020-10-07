#include "../hooks.h"

void __fastcall c_hooks::c_fire_events::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	original(ecx, edx);
}
