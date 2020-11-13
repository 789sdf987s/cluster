#include "../hooks.h"
#include "../../../../game/definitions.h"
#include "../../../../game/classes/view_setup.h"
#include "../../../features/features.h"

void __fastcall c_hooks::c_override_view::hook(REGISTERS, c_view_setup* view) {
	if (g_hooks.is_unhooking)
		return original(ecx, edx, view);

	static c_convar* cam_ideallag = g_interfaces.convar->find_convar("cam_ideallag");
	cam_ideallag->set_int(0);

	g_features.thirdperson.on_override_view();
	original(ecx, edx, view);
}
