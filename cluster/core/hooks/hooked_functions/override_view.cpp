#include "../hooks.h"
#include "../../../../game/definitions.h"
#include "../../../../game/classes/view_setup.h"

void __fastcall c_hooks::c_override_view::hook(REGISTERS, c_view_setup* view) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, view);

	original(ecx, edx, view);
}
