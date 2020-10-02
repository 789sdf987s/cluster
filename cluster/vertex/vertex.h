#pragma once
#include <d3d9.h>
#include "../color/color.h"

class vertex_t {
public:
	float x, y, z, rhw;
	D3DCOLOR color;

	vertex_t() = default;
	vertex_t(const float x, const float y, color_t color) {
		this->x = x;
		this->y = y;
		this->color = color.dx_color();
	}
	vertex_t(int x, int y, color_t color) {
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
		this->color = color.dx_color();
	}
};