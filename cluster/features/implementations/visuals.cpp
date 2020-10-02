#include "visuals.h"

void c_visuals::populate_render_list() {
	if (!g_globals.local_player)
		return;

	for (int i = 0; i < g_interfaces.engine->get_max_clients(); i++) {
		player_t* player = reinterpret_cast<player_t*>(g_interfaces.entity_list->get_client_entity(i));
		if (!player || !player->is_player() || player->team() == g_globals.local_player->team() || player->health() <= 0)
			continue;

		box_t box;
		if (!this->calculate_box(player, box))
			continue;

		player_info_t info;
		g_interfaces.engine->get_player_info(player->index(), &info);

		this->render_box(player, box);
		this->render_name(player, box, info);
		this->render_flags(player, box, info);
	}
}

bool c_visuals::calculate_box(entity_t* entity, box_t& box) {
	matrix_t& coordinate_frame = entity->coordinate_frame();
	const vector3_t mins = entity->mins();
	const vector3_t maxs = entity->maxs();

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

void c_visuals::render_box(entity_t* entity, box_t& box) {
	g_renderer.render_rectangle(box.x - 1, box.y - 1, box.width + 2, box.height + 2, color_t(0, 0, 0, 200));
	g_renderer.render_rectangle(box.x + 1, box.y + 1, box.width - 2, box.height - 2, color_t(0, 0, 0, 200));
	g_renderer.render_rectangle(box.x, box.y, box.width, box.height, color_t(255, 255, 255, 255));
}

void c_visuals::render_name(entity_t* entity, box_t& box, player_info_t& info) {
	g_renderer.render_text(box.x + (box.width / 2), box.y - 2, HORIZONTAL_CENTER | VERTICAL_TOP, DROPSHADOW, info.name, g_renderer.fonts.tahoma, color_t(255, 255, 255, 255));
}

void c_visuals::render_flags(player_t* player, box_t& box, player_info_t& info) {
	text_size_t flag_size;

	if (info.fake_player)
		flag_size = g_renderer.render_text(box.x - 2, box.y, HORIZONTAL_LEFT | VERTICAL_BOTTOM, OUTLINE, "bot", g_renderer.fonts.smallest_font, color_t(255, 255, 255, 255));

	unsigned short step = 0;
	flag_size += g_renderer.render_text(box.x + box.width + 3, box.y, DEFAULT, OUTLINE, "$" + std::to_string(player->money()), g_renderer.fonts.smallest_font, color_t(255 / 2, 255, 255 / 2, 255));
}