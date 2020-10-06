#include "visuals.h"

void c_visuals::populate_render_list() {
	if (!g_globals.local_player)
		return;

	for (int i = 0; i < g_interfaces.engine->get_max_clients(); i++) {
		player = reinterpret_cast<player_t*>(g_interfaces.entity_list->get_client_entity(i));
		if (!player || !player->is_player() || player->team() == g_globals.local_player->team() || player->health() <= 0)
			continue;

		box_t box;
		if (!this->calculate_box(box))
			continue;

		player_info_t info;
		g_interfaces.engine->get_player_info(player->index(), &info);

		this->render_box(box);
		this->render_name(box, info);
		this->render_flags(box, info);
		this->render_health(box);
	}
}

const color_t c_visuals::scale_color(const color_t& color) {
	if (!player->is_dormant())
		return color;

	unsigned const short color_average = (color.r + color.g + color.b) / 3;
	unsigned const short alpha = std::clamp(color.a / 2, 0, 255);
	unsigned const short distance = alpha - static_cast<unsigned const short>(std::clamp((player->origin() - g_globals.local_player->origin()).length_2d(), 0.f, static_cast<float>(alpha)));

	return color_t(color_average, color_average, color_average, alpha - distance);
}

bool c_visuals::calculate_box(box_t& box) {
	matrix_t& coordinate_frame = player->coordinate_frame();
	const vector3_t mins = player->mins();
	const vector3_t maxs = player->maxs();

	vector3_t screen_boxes[8];
	for (unsigned short i = 0; i < 8; i++) {
		vector3_t point = {
			i & 1 ? maxs.x : mins.x,
			i & 2 ? maxs.y : mins.y,
			i & 4 ? maxs.z : mins.z
		};

		if (!g_math.world_to_screen(g_math.transform_vector(point, coordinate_frame), screen_boxes[i]))
			return false;
	}

	const vector3_t box_array[] = {
		screen_boxes[3],
		screen_boxes[5],
		screen_boxes[0],
		screen_boxes[4],
		screen_boxes[2],
		screen_boxes[1],
		screen_boxes[6],
		screen_boxes[7]
	};

	float left = screen_boxes[3].x, bottom = screen_boxes[3].y, right = screen_boxes[3].x, top = screen_boxes[3].y;

	for (int i = 0; i <= 7; i++) {
		if (left > box_array[i].x)
			left = box_array[i].x;

		if (bottom < box_array[i].y)
			bottom = box_array[i].y;

		if (right < box_array[i].x)
			right = box_array[i].x;

		if (top > box_array[i].y)
			top = box_array[i].y;
	}

	box.x = static_cast<int>(left);
	box.y = static_cast<int>(top);
	box.width = static_cast<int>(right) - static_cast<int>(left);
	box.height = static_cast<int>(bottom) - static_cast<int>(top);
	return true;
}

void c_visuals::render_box(box_t& box) {
	g_renderer.render_rectangle(box.x - 1, box.y - 1, box.width + 2, box.height + 2, color_ts(0, 0, 0, 150));
	g_renderer.render_rectangle(box.x + 1, box.y + 1, box.width - 2, box.height - 2, color_ts(0, 0, 0, 150));
	g_renderer.render_rectangle(box.x, box.y, box.width, box.height, color_ts(255, 255, 255, 225));
}

void c_visuals::render_name(box_t& box, player_info_t& info) {
	g_renderer.render_text(box.x + (box.width / 2), box.y - 2, HORIZONTAL_CENTER | VERTICAL_TOP, DROPSHADOW, info.name, g_renderer.fonts.tahoma, color_ts(255, 255, 255, 255));
}

void c_visuals::render_flags(box_t& box, player_info_t& info) {
	unsigned short flag_height = 0U;

	if (info.fake_player)
		RENDER_FLAG("bot", color_ts(255, 255, 255, 225));

	RENDER_FLAG("$" + std::to_string(player->money()), color_ts(255 / 2, 255, 255 / 2, 225));
}

void c_visuals::render_health(box_t& box) {
	const int health = std::clamp(player->health(), 0, 100);
	const unsigned short health_color_scaled = static_cast<const unsigned short>(health * 2.55f);
	const unsigned short bar_height = static_cast<const unsigned short>(box.height * (health / 100.f));

	g_renderer.render_filled_rectangle(box.x - 6, box.y - 1, 4, box.height + 2, color_ts(0, 0, 0, 85));
	g_renderer.render_rectangle(box.x - 6, box.y - 1, 4, box.height + 2, color_ts(0, 0, 0, 20));
	g_renderer.render_filled_rectangle(box.x - 5, box.y + box.height - bar_height, 2, bar_height, color_ts(255 - (health_color_scaled / 2), health_color_scaled, 0, 225));
	g_renderer.render_text(box.x - 7, box.y + box.height - bar_height, HORIZONTAL_LEFT | VERTICAL_CENTER, DROPSHADOW, std::to_string(health), g_renderer.fonts.smallest_pixel_7, color_ts(255, 255, 255, 225));
}
