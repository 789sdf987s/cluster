#include "../hooks.h"
#include <intrin.h>

void __fastcall c_hooks::c_calc_view_bob::hook(REGISTERS, vector3_t& eye_origin) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, eye_origin);

	original(ecx, edx, eye_origin);
}
