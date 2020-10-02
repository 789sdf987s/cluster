#pragma once
#include "../../cluster/vector/vector3.h"
#include <type_traits>

class i_debug_overlay {
public:
	bool world_to_screen(const vector3_t& in, vector3_t& out) {
		using original_fn = int(__thiscall*)(i_debug_overlay*, const vector3_t&, vector3_t&);
		int return_value = (*(original_fn**)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}

	bool screen_position(const vector3_t& in, vector3_t& out) {
		using original_fn = bool(__thiscall*)(i_debug_overlay*, const vector3_t&, vector3_t&);
		return (*(original_fn**)this)[11](this, std::ref(in), std::ref(out));
	}

	void draw_pill(vector3_t& abs_min, vector3_t& abs_max, float radius, int r, int g, int b, int a, float duration) {
		using original_fn = void(__thiscall*)(i_debug_overlay*, vector3_t&, vector3_t&, float, int, int, int, int, float);
		(*(original_fn**)this)[24](this, abs_min, abs_max, radius, r, g, b, a, duration);
	}
};