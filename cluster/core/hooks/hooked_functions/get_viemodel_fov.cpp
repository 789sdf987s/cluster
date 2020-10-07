#include "../hooks.h"

float __fastcall c_hooks::c_get_viewmodel_fov::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	return original(ecx, edx);
}
