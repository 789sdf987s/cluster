#include "../hooks.h"

bool __fastcall c_hooks::c_is_using_static_prop_debug::hook( REGISTERS ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx );

	return true;
}
