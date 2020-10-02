#pragma once
#include <d3d9.h>

class color_t {
public:
	int a, r, g, b;
	color_t() = default;
	color_t(const int r, const int g, const int b, const int a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	explicit color_t(const unsigned long color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}

	__forceinline D3DCOLOR dx_color() {
		return D3DCOLOR_ARGB(this->a, this->r, this->g, this->b);
	}
};