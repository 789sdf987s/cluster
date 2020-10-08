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

	if (!c_is_hltv::create_hook(get_virtual(g_interfaces.engine, 93)))
		return false;

	if (!c_list_leaves_in_box::create_hook(get_virtual(g_interfaces.engine->get_bsp_tree_query(), 6)))
		return false;

	std::uint8_t* player_vtable = g_utilities.signature_scan("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 89 7C 24 0C");
	if (!player_vtable) {
		g_console.error("failed to find player vtable");
		return false;
	}

	player_vtable += 0x47;

	if (!c_is_following_entity::create_hook(get_virtual(player_vtable, 177)))
		return false;

	std::uint8_t* should_skip_animation_frame_signature = g_utilities.signature_scan("client.dll", "57 8B F9 8B 07 8B 80 ? ? ? ? FF D0 84 C0 75 02 5F C3");
	if (!should_skip_animation_frame_signature) {
		g_console.error("failed to hook should_skip_animation_frame");
		return false;
	}

	if (!c_should_skip_animation_frame::create_hook(should_skip_animation_frame_signature))
		return false;

	if (!c_standard_blending_rules::create_hook(get_virtual(player_vtable, 205)))
		return false;

	if (!c_update_client_side_animations::create_hook(get_virtual(player_vtable, 223)))
		return false;

	std::uint8_t* do_procedural_foot_plant_signature = g_utilities.signature_scan("client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 57 8B 56 60");
	if (!do_procedural_foot_plant_signature) {
		g_console.error("failed to hook do_procedural_foot_plant");
		return false;
	}

	if (!c_do_procedural_foot_plant::create_hook(do_procedural_foot_plant_signature))
		return false;

	std::uint8_t* setup_bones_signature = g_utilities.signature_scan("client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9 8B 0D");
	if (!setup_bones_signature) {
		g_console.error("failed to hook setup_bones");
		return false;
	}

	if (!c_setup_bones::create_hook(setup_bones_signature))
		return false;

	std::uint8_t* get_view_angles_signature = g_utilities.signature_scan("client.dll", "56 8B F1 85 F6 74 32");
	if (!get_view_angles_signature) {
		g_console.error("failed to hook get_view_angles");
		return false;
	}

	if (!c_get_view_angles::create_hook(get_view_angles_signature))
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
