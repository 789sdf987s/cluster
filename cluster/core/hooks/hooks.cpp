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

	c_wnd_proc::set( );

	return MH_EnableHook( MH_ALL_HOOKS ) == MH_OK;
}

void c_hooks::unhook_all( ) {
	c_wnd_proc::restore( );

	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}

c_hooks g_hooks;
