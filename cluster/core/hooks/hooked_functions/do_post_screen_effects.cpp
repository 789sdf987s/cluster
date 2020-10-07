#include "../hooks.h"

int __fastcall c_hooks::c_do_post_screen_effects::hook(REGISTERS, c_view_setup* view_setup) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, view_setup);

	original(ecx, edx, view_setup);
}
