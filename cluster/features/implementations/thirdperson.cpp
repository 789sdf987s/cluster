#include "thirdperson.h"

void c_thirdperson::on_override_view() {
	//if (!g_interfaces.engine->is_in_game() || !g_globals.local_player)
	//	return;

	//static vector3_t angles;
	//g_interfaces.engine->get_view_angles(angles);

	//if (g_globals.local_player->health() > 0 && (GetAsyncKeyState(VK_XBUTTON2) & 0x8000)) {
	//	if (!g_interfaces.input->is_camera_in_third_person) {
	//		auto get_correct_distance = [&](float ideal_distance) -> float {
	//			vector3_t inversed_angles;
	//			g_interfaces.engine->get_view_angles(inversed_angles);

	//			inversed_angles.x *= -1.f, inversed_angles.y += 180.f;

	//			vector3_t direction;
	//			g_math.angle_vectors(inversed_angles, direction);

	//			ray_t ray(csgo::local_player->get_eye_pos(), csgo::local_player->get_eye_pos() + (direction * ideal_distance));
	//			trace_t trace;
	//			trace_filter_skip_one_entity filter(csgo::local_player);

	//			interfaces::trace_ray->trace_ray(ray, MASK_SHOT, &filter, &trace);

	//			return (ideal_distance * trace.flFraction) - 10.f;
	//		};

	//		angles.z = get_correct_distance(100.f);

	//		interfaces::input->camera_in_third_person = true;

	//		interfaces::input->camera_offset = vec3_t(angles.x, angles.y, angles.z);
	//	}
	//}
	//else {
	//	interfaces::input->camera_in_third_person = false;

	//	interfaces::input->camera_offset = vec3_t(angles.x, angles.y, 0);
	//}
}
