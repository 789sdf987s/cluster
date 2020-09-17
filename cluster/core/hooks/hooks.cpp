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

	c_wnd_proc::set( );

	return MH_EnableHook( MH_ALL_HOOKS ) == MH_OK;
}

void c_hooks::unhook_all( ) {
	c_wnd_proc::restore( );

	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}

c_hooks g_hooks;
