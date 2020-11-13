#include "../hooks.h"

void __fastcall c_hooks::c_get_screen_aspect_ratio::hook( REGISTERS, int w, int h ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx, w, h );

	original( ecx, edx, w, h );
}
