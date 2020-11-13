#include "../hooks.h"

int __fastcall c_hooks::c_list_leaves_in_box::hook( REGISTERS, const vector3_t& mins, const vector3_t& maxs, unsigned short* list, int list_max ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx, mins, maxs, list, list_max );

	return original( ecx, edx, mins, maxs, list, list_max );
}
