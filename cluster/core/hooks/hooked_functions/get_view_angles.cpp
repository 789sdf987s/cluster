#include "../hooks.h"

vector3_t* __fastcall c_hooks::c_get_view_angles::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	return original(ecx, edx);
}
