#pragma once
#include <cstdint>
#include "../vector/vector3.h"
#include "../utilities/utilities.h"
#include "../view_matrix/view_matrix.h"
#include "../core/interfaces/interfaces.h"

class c_math {
public:
	inline void normalize_angle(vector3_t& angle) {
		angle.x = std::isfinite(angle.x) ? std::remainderf(angle.x, 360.0f) : 0.0f;
		angle.y = std::isfinite(angle.y) ? std::remainderf(angle.y, 360.0f) : 0.0f;
	}

	bool world_to_screen(const vector3_t& world, vector3_t& screen);
	bool screen_transform(const vector3_t& world, vector3_t& screen);

	inline vector3_t transform_vector(vector3_t& in, matrix_t& matrix) {
		return vector3_t(
			in.dot(matrix[0]) + matrix[0][3],
			in.dot(matrix[1]) + matrix[1][3],
			in.dot(matrix[2]) + matrix[2][3]);
	}
};

extern c_math g_math;