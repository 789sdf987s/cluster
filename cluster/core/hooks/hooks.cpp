#include "hooks.h"

bool c_hooks::hook_all( ) {
	if ( MH_Initialize( ) != MH_OK )
		return false;

	if ( !c_create_move::create_hook( get_virtual( g_interfaces.client_mode, 24 ) ) )
		return false;



	return MH_EnableHook( MH_ALL_HOOKS ) == MH_OK;
}

void c_hooks::unhook_all( ) {
	MH_DisableHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}

c_hooks g_hooks;
