#include "../hooks.h"

void __fastcall c_hooks::c_do_procedural_foot_plant::hook( REGISTERS, int a1, int a2, int a3, int a4 ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx, a1, a2, a3, a4 );

	return;
}
