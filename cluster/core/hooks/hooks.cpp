#include "hooks.h"

bool c_hooks::hook_all( ) {
	if ( MH_Initialize( ) != MH_OK )
		return false;

	if ( !c_create_move::create_hook( get_virtual( g_interfaces.client_mode, 24 ) ) )
		return false;

	if ( !c_paint_traverse::create_hook( get_virtual( g_interfaces.panel, 41 ) ) )
		return false;

	if ( !c_end_scene::create_hook( get_virtual( g_interfaces.direct_x, 42 ) ) )
		return false;

	if ( !c_reset::create_hook( get_virtual( g_interfaces.direct_x, 16 ) ) )
		return false;

	if ( !c_frame_stage_notify::create_hook( get_virtual( g_interfaces.client, 37 ) ) )
		return false;

	std::optional<std::uint8_t*> check_file_crcs_with_server_signature = g_utilities.signature_scan( "engine.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 89 5D F8 80" );
	if ( !check_file_crcs_with_server_signature.has_value( ) ) {
		g_console.error( "failed to hook check_file_crcs_with_server" );
		return false;
	}

	if ( !c_check_file_crcs_with_server::create_hook( check_file_crcs_with_server_signature.value( ) ) )
		return false;

	if ( !c_loose_file_allowed::create_hook( get_virtual( g_interfaces.file_system, 128 ) ) )
		return false;

	if ( !c_draw_model_execute::create_hook( get_virtual( g_interfaces.model_render, 21 ) ) )
		return false;

	std::optional<std::uint8_t*> lock_cursor_signature = g_utilities.signature_scan( "vguimatsurface.dll", "80 3D ? ? ? ? 00 8B 91 A4 02 00 00 8B 0D ? ? ? ? C6 05 ? ? ? ? 01" );
	if ( !lock_cursor_signature.has_value( ) ) {
		g_console.error( "failed to hook lock_cursor" );
		return false;
	}

	if ( !c_lock_cursor::create_hook( lock_cursor_signature.value( ) ) )
		return false;

	c_wnd_proc::set( );

	return MH_EnableHook( MH_ALL_HOOKS ) == MH_OK;
}

void c_hooks::unhook_all( ) {
	c_wnd_proc::restore( );

	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}

c_hooks g_hooks;
