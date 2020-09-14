#include "../hooks.h"

bool __fastcall c_hooks::c_create_move::hook( REGISTERS, float input_sample_frametime, c_usercmd* cmd ) {
	bool to_return = original( ecx, edx, input_sample_frametime, cmd );



	return to_return;
}
