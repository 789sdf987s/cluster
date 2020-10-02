#pragma once
#include "../../vector/vector3.h"
#include "../../../game/classes/entities.h"
#include "../../math/math.h"
#include "../../globals/globals.h"
#include "../../features/helpers/renderer.h"

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
};