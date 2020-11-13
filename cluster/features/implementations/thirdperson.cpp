#include "thirdperson.h"

void c_thirdperson::on_override_view( ) {
	if ( !g_interfaces.engine->is_in_game( ) || !g_globals.local_player || g_globals.local_player->health( ) <= 0 ) {
		g_interfaces.input->is_camera_in_third_person = false;
		return;
	}

	auto get_correct_distance = [ ] ( float ideal_distance ) -> float {
		vector3_t inversed_angles;
		g_interfaces.engine->get_view_angles( inversed_angles );

		inversed_angles.x *= -1.f, inversed_angles.y += 180.f;

		vector3_t direction;
		g_math.angle_vectors( inversed_angles, direction );

		ray_t ray( g_globals.local_player->eye_position( ), g_globals.local_player->eye_position( ) + ( direction * ideal_distance ) );
		trace_t trace;
		c_trace_filter_skip_all filter;

		g_interfaces.trace->trace_ray( ray, MASK_SHOT, &filter, &trace );

		return ( ideal_distance * trace.fraction ) - 10.f;
	};

	const bool is_button_down = GetAsyncKeyState( VK_XBUTTON2 ) & 0x8000;
	static bool was_button_down, should_be_in_thirdperson;

	if ( is_button_down && !was_button_down )
		should_be_in_thirdperson = !should_be_in_thirdperson;

	g_interfaces.input->is_camera_in_third_person = should_be_in_thirdperson;
	g_interfaces.input->camera_offset.z = g_interfaces.input->is_camera_in_third_person ? get_correct_distance( 100.f ) : 0.f;

	was_button_down = is_button_down;
}
