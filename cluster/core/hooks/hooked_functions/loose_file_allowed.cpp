#include "../hooks.h"

bool __fastcall c_hooks::c_loose_file_allowed::hook( REGISTERS ) {
	return original( ecx, edx );
}
