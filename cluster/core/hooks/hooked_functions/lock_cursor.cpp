#include "../hooks.h"
#include "../../../features/features.h"

void __fastcall c_hooks::c_lock_cursor::hook( REGISTERS ) {
	if ( g_hooks.is_unhooking || g_features.menu.is_open )
		return g_interfaces.surface->unlock_cursor( );

	original( ecx, edx );
}
