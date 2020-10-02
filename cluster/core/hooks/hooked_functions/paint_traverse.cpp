#include "../hooks.h"

void __fastcall c_hooks::c_paint_traverse::hook(REGISTERS, unsigned int panel, bool force_repaint, bool allow_force) {
	original(ecx, edx, panel, force_repaint, allow_force);
}
