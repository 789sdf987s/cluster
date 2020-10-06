#include "../hooks.h"
#include "../../../../game/definitions.h"

void __fastcall c_hooks::c_frame_stage_notify::hook(REGISTERS, client_frame_stage_t stage) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, stage);

	original(ecx, edx, stage);
}
