#include "../hooks.h"

void __fastcall c_hooks::c_fire_event::hook( REGISTERS, i_game_event* event, bool done_broadcast ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx, event, done_broadcast );

	original( ecx, edx, event, done_broadcast );
}
