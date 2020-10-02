#include "../hooks.h"
#include "../../../../game/classes/models.h"

void __fastcall c_hooks::c_draw_model_execute::hook(REGISTERS, void* ctx, void* state, model_render_info_t& info, matrix_t* bone_to_world) {
	original(ecx, edx, ctx, state, info, bone_to_world);
}
