#pragma once
#include "../vector/vector3.h"

class c_math {
public:
	inline void normalize_angle( vector3_t& angle ) {
		angle.x = std::isfinite( angle.x ) ? std::remainderf( angle.x, 360.0f ) : 0.0f;
		angle.y = std::isfinite( angle.y ) ? std::remainderf( angle.y, 360.0f ) : 0.0f;
	}
};

extern c_math g_math;