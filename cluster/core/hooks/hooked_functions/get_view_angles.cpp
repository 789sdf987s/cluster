#include "../hooks.h"
#include "../../../globals/globals.h"
#include <intrin.h>

vector3_t* __fastcall c_hooks::c_get_view_angles::hook( REGISTERS ) {
	if ( g_hooks.is_unhooking || ecx != g_globals.local_player || !g_interfaces.input->is_camera_in_third_person )
		return original( ecx, edx );

	const std::uintptr_t return_address = reinterpret_cast< std::uintptr_t >( _ReturnAddress( ) );

	static std::uintptr_t thirdperson_pitch_return = reinterpret_cast< std::uintptr_t > ( g_utilities.signature_scan( "client.dll", "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55" ) );
	static std::uintptr_t thirdperson_yaw_return = reinterpret_cast< std::uintptr_t >( g_utilities.signature_scan( "client.dll", "F3 0F 10 55 ? 51 8B 8E ? ? ? ?" ) );

	if ( return_address == thirdperson_pitch_return ||
		return_address == thirdperson_yaw_return )
		return &g_globals.thirdperson_angles;

	return original( ecx, edx );
}
