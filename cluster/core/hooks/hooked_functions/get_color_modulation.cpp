#include "../hooks.h"

void __fastcall c_hooks::c_get_color_modulation::hook(REGISTERS, float* r, float* g, float* b) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, r, g, b);

	original(ecx, edx, r, g, b);
}
