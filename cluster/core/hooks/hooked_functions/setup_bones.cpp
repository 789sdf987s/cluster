#include "../hooks.h"

bool __fastcall c_hooks::c_setup_bones::hook(REGISTERS, matrix_t* bone_to_world_out, int max_bones, int bone_mask, float current_time) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, bone_to_world_out, max_bones, bone_mask, current_time);

	return original(ecx, edx, bone_to_world_out, max_bones, bone_mask, current_time);
}
