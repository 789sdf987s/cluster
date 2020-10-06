#include <algorithm>
#include "../hooks.h"
#include "../../../math/math.h"
#include "../../../features/features.h"

bool __fastcall c_hooks::c_create_move::hook(REGISTERS, float input_sample_frametime, c_usercmd* cmd) {
	original(ecx, edx, input_sample_frametime, cmd);

	if (g_hooks.is_unhooking)
		return false;

	g_globals.local_player = reinterpret_cast<player_t*>(g_interfaces.entity_list->get_client_entity(g_interfaces.engine->get_local_player()));

	if (g_features.menu.is_open) {
		cmd->buttons &= ~in_attack;
		cmd->buttons &= ~in_attack2;
	}

	g_math.normalize_angle(cmd->viewangles);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.f, 450.f);
	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.f, 450.f);
	return false;
}
