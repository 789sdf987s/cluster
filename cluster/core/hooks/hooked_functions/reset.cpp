#include "../hooks.h"
#include "../../../features/features.h"

long __fastcall c_hooks::c_reset::hook( REGISTERS, IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters ) {
	g_features.menu.pre_reset( );
	long result = original( ecx, edx, device, presentation_parameters );
	g_features.menu.post_reset( );

	return result;
}