#include "../hooks.h"

bool __fastcall c_hooks::c_is_hltv::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	return original(ecx, edx);
}
