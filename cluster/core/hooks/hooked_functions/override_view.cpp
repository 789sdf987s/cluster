#include "../hooks.h"
#include "../../../../game/definitions.h"
#include "../../../../game/classes/view_setup.h"

void __fastcall c_hooks::c_override_view::hook( REGISTERS, c_view_setup* view ) {
	original( ecx, edx, view );
}
