#include "../hooks.h"

void __fastcall c_hooks::c_calc_view::hook( REGISTERS, vector3_t& eye_origin, vector3_t& eye_angles, float& z_near, float& z_far, float& fov ) {
	if ( g_hooks.is_unhooking )
		return original( ecx, edx, eye_origin, eye_angles, z_near, z_far, fov );

	original( ecx, edx, eye_origin, eye_angles, z_near, z_far, fov );
}
