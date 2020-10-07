#include "hooks.h"

bool c_hooks::hook_all() {
	if (MH_Initialize() != MH_OK)
		return false;

	if (!c_create_move::create_hook(get_virtual(g_interfaces.client_mode, 24)))
		return false;

	if (!c_paint_traverse::create_hook(get_virtual(g_interfaces.panel, 41)))
		return false;

	if (!c_end_scene::create_hook(get_virtual(g_interfaces.direct_x, 42)))
		return false;

	if (!c_reset::create_hook(get_virtual(g_interfaces.direct_x, 16)))
		return false;

	if (!c_frame_stage_notify::create_hook(get_virtual(g_interfaces.client, 37)))
		return false;

	std::uint8_t* check_file_crcs_with_server_signature = g_utilities.signature_scan("engine.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80");
	if (!check_file_crcs_with_server_signature) {
		g_console.error("failed to hook check_file_crcs_with_server");
		return false;
	}

	if (!c_check_file_crcs_with_server::create_hook(check_file_crcs_with_server_signature))
		return false;

	if (!c_loose_file_allowed::create_hook(get_virtual(g_interfaces.file_system, 128)))
		return false;

	if (!c_draw_model_execute::create_hook(get_virtual(g_interfaces.model_render, 21)))
		return false;

	std::uint8_t* lock_cursor_signature = g_utilities.signature_scan("vguimatsurface.dll", "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01");
	if (!lock_cursor_signature) {
		g_console.error("failed to hook lock_cursor");
		return false;
	}

	if (!c_lock_cursor::create_hook(lock_cursor_signature))
		return false;

	if (!c_get_viewmodel_fov::create_hook(get_virtual(g_interfaces.client_mode, 35)))
		return false;

	std::uint8_t* get_color_modulation_signature = g_utilities.signature_scan("materialsystem.dll", "55 8B EC 83 EC ? 56 8B F1 8A 46");
	if (!get_color_modulation_signature) {
		g_console.error("failed to hook get_color_modulation");
		return false;
	}

	if (!c_get_color_modulation::create_hook(get_color_modulation_signature))
		return false;

	if (!c_get_screen_aspect_ratio::create_hook(get_virtual(g_interfaces.engine, 101)))
		return false;

	std::uint8_t* is_using_static_prop_debug_signature = g_utilities.signature_scan("engine.dll", "8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 ? A1 ? ? ? ? 35 ? ? ? ? EB ? 8B 01 FF 50 ? 83 F8 ? 0F 85 ? ? ? ? 8B 0D");
	if (!is_using_static_prop_debug_signature) {
		g_console.error("failed to hook is_using_static_prop_debug");
		return false;
	}

	if (!c_is_using_static_prop_debug::create_hook(is_using_static_prop_debug_signature))
		return false;

	if (!c_convar_get_bool::create_hook(get_virtual(g_interfaces.convar->find_convar("sv_cheats"), 13)))
		return false;

	if (!c_do_post_screen_effects::create_hook(get_virtual(g_interfaces.client_mode, 44)))
		return false;

	if (!c_is_connected::create_hook(get_virtual(g_interfaces.engine, 27)))
		return false;

	if (!c_fire_events::create_hook(get_virtual(g_interfaces.engine, 59)))
		return false;

	c_wnd_proc::set();

	return MH_EnableHook(MH_ALL_HOOKS) == MH_OK;
}

void c_hooks::unhook_all() {
	is_unhooking = true;
	g_utilities.sleep(5);

	c_wnd_proc::restore();

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

c_hooks g_hooks;
