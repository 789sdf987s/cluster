#include "../hooks.h"

bool __fastcall c_hooks::c_write_user_cmd_to_buffer::hook(REGISTERS, int slot, bf_write* buffer, int from, int to, bool is_new_cmd) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, slot, buffer, from, to, is_new_cmd);

	return original(ecx, edx, slot, buffer, from, to, is_new_cmd);
}
