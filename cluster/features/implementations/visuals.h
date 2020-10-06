#pragma once
#include "../../vector/vector3.h"
#include "../../../game/classes/entities.h"
#include "../../math/math.h"
#include "../../globals/globals.h"
#include "../../features/helpers/renderer.h"

#define RENDER_FLAG(name, color) flag_height += g_renderer.render_text(box.x + box.width + 3, box.y + flag_height, DEFAULT, DROPSHADOW, name, g_renderer.fonts.smallest_pixel_7, color).height

class box_t {
public:
	int x, y, width, height;
};

class c_visuals {
public:
	void populate_render_list();

private:
	bool calculate_box(entity_t* entity, box_t& box);
	void render_box(entity_t* entity, box_t& box);
	void render_name(entity_t* entity, box_t& box, player_info_t& info);
	void render_flags(player_t* player, box_t& box, player_info_t& info);
	void render_health(player_t* player, box_t& box);
};