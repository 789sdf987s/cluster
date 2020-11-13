#include "../hooks.h"
#include "../../../../game/classes/event_info.h"

void __fastcall c_hooks::c_fire_events::hook( REGISTERS ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx );

	if ( g_interfaces.engine->is_in_game( ) ) {
		for ( event_info_t* event_info = g_interfaces.client_state->events; event_info != nullptr; event_info = event_info->next_info )
			event_info->fire_delay = 0.f;
	}

	original( ecx, edx );
}
