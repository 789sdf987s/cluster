#include "../hooks.h"

void __fastcall c_hooks::c_check_file_crcs_with_server::hook(REGISTERS) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx);

	original(ecx, edx);
}
