#pragma once
#include "../../vector/vector3.h"
#include "../../../game/classes/entities.h"
#include "../../math/math.h"
#include "../../globals/globals.h"
#include "../../features/helpers/renderer.h"

#define RENDER_FLAG(name, color) flag_height += g_renderer.render_text(box.x + box.width + 3, box.y + flag_height, DEFAULT, DROPSHADOW, name, g_renderer.fonts.smallest_pixel_7, color).height
#define color_ts(r, g, b, a) this->scale_color(color_t(r, g, b, a))

class box_t {
public:
	int x, y, width, height;
};

class c_visuals {
public:
	void populate_render_list( );

private:
	player_t* player;

	const color_t scale_color( const color_t& color );
	bool calculate_box( box_t& box );
	void render_box( box_t& box );
	void render_name( box_t& box, player_info_t& info );
	void render_flags( box_t& box, player_info_t& info );
	void render_health( box_t& box );
};
