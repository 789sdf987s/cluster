#pragma once
#include <cstdint>
#include "../vector/vector3.h"
#include "../utilities/utilities.h"
#include "../view_matrix/view_matrix.h"
#include "../core/interfaces/interfaces.h"

constexpr double M_PI = 3.14159265358979323846;
constexpr float M_RADPI = 57.295779513082f;
constexpr float M_PI_F = static_cast<float>(M_PI);

class c_math {
public:
	constexpr float RAD_2_DEG(const float x) {
		return static_cast<float>(x) * static_cast<float>(180.f / M_PI_F);
	}

	constexpr float DEG_2_RAD(const float x) {
		return static_cast<float>(x) * static_cast<float>(M_PI_F / 180.f);
	}

	inline void sin_cos(const float rad, float& sine, float& cosine) {
		sine = std::sin(rad);
		cosine = std::cos(rad);
	}

	inline void normalize_angle(vector3_t& angle) {
		angle.x = std::isfinite(angle.x) ? std::remainderf(angle.x, 360.0f) : 0.0f;
		angle.y = std::isfinite(angle.y) ? std::remainderf(angle.y, 360.0f) : 0.0f;
	}

	bool world_to_screen(const vector3_t& world, vector3_t& screen);
	bool screen_transform(const vector3_t& world, vector3_t& screen);

	void angle_vectors(const vector3_t& angle, vector3_t& out);

	inline vector3_t transform_vector(vector3_t& in, matrix_t& matrix) {
		return vector3_t(
			in.dot(matrix[0]) + matrix[0][3],
			in.dot(matrix[1]) + matrix[1][3],
			in.dot(matrix[2]) + matrix[2][3]);
	}
};

extern c_math g_math;