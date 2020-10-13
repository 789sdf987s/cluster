#include "../hooks.h"
#include "../../../../game/classes/entities.h"

void __fastcall c_hooks::c_standard_blending_rules::hook(REGISTERS, void* studio_hdr, vector3_t* position, void* quaternion, float current_time, int bone_mask) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, studio_hdr, position, quaternion, current_time, bone_mask);

	entity_t* entity = reinterpret_cast<entity_t*>(ecx);
	entity->effects() |= 8;

	original(ecx, edx, studio_hdr, position, quaternion, current_time, bone_mask);

	entity->effects() &= ~8;
}
