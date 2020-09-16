#include "../hooks.h"
#include "../../../features/features.h"

long __fastcall c_hooks::c_reset::hook( REGISTERS, IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters ) {
	g_features.menu.reset( true );
	long result = original( ecx, edx, device, presentation_parameters );
	g_features.menu.reset( false );

	return result;
}