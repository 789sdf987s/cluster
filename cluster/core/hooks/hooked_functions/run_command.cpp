#include "../hooks.h"

void __fastcall c_hooks::c_run_command::hook(REGISTERS, entity_t* entity, c_usercmd* cmd, void* move_helper) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, entity, cmd, move_helper);

	original(ecx, edx, entity, cmd, move_helper);
}
