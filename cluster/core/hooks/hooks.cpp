#include "hooks.h"

bool c_hooks::hook_all() {
	if (MH_Initialize() != MH_OK)
		return false;

	std::uint8_t* player_vtable = g_utilities.signature_scan("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 89 7C 24 0C");
	if (!player_vtable) {
		g_console.error("failed to find player vtable");
		return false;
	}

	player_vtable += 0x47;

	if (!c_create_move::create_hook(g_interfaces.client_mode, 24))
		return false;

	if (!c_paint_traverse::create_hook(g_interfaces.panel, 41))
		return false;

	if (!c_end_scene::create_hook(g_interfaces.direct_x, 42))
		return false;

	if (!c_reset::create_hook(g_interfaces.direct_x, 16))
		return false;

	if (!c_frame_stage_notify::create_hook(g_interfaces.client, 37))
		return false;

	if (!c_check_file_crcs_with_server::create_hook("engine.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80"))
		return false;

	if (!c_loose_file_allowed::create_hook(g_interfaces.file_system, 128))
		return false;

	if (!c_draw_model_execute::create_hook(g_interfaces.model_render, 21))
		return false;

	if (!c_lock_cursor::create_hook("vguimatsurface.dll", "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01"))
		return false;

	if (!c_get_viewmodel_fov::create_hook(g_interfaces.client_mode, 35))
		return false;

	if (!c_get_color_modulation::create_hook("materialsystem.dll", "55 8B EC 83 EC ? 56 8B F1 8A 46"))
		return false;

	if (!c_get_screen_aspect_ratio::create_hook(g_interfaces.engine, 101))
		return false;

	if (!c_is_using_static_prop_debug::create_hook("engine.dll", "8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 ? A1 ? ? ? ? 35 ? ? ? ? EB ? 8B 01 FF 50 ? 83 F8 ? 0F 85 ? ? ? ? 8B 0D"))
		return false;

	if (!c_convar_get_bool::create_hook(g_interfaces.convar->find_convar("sv_cheats"), 13))
		return false;

	if (!c_do_post_screen_effects::create_hook(g_interfaces.client_mode, 44))
		return false;

	if (!c_is_connected::create_hook(g_interfaces.engine, 27))
		return false;

	if (!c_fire_events::create_hook(g_interfaces.engine, 59))
		return false;

	if (!c_is_hltv::create_hook(g_interfaces.engine, 93))
		return false;

	if (!c_list_leaves_in_box::create_hook(g_interfaces.engine->get_bsp_tree_query(), 6))
		return false;

	if (!c_is_following_entity::create_hook(player_vtable, 177))
		return false;

	if (!c_should_skip_animation_frame::create_hook("client.dll", "57 8B F9 8B 07 8B 80 ? ? ? ? FF D0 84 C0 75 02 5F C3"))
		return false;

	if (!c_standard_blending_rules::create_hook(player_vtable, 205))
		return false;

	if (!c_update_client_side_animations::create_hook(player_vtable, 223))
		return false;

	if (!c_do_procedural_foot_plant::create_hook("client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 57 8B 56 60"))
		return false;

	if (!c_setup_bones::create_hook("client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 57 8B F9 8B 0D"))
		return false;

	if (!c_get_view_angles::create_hook("client.dll", "56 8B F1 85 F6 74 32"))
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
