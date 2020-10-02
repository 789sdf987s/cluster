#pragma once
#include <limits>
#include "../vector/vector3.h"

class matrix_t {
public:
	matrix_t() {
		this->invalidate();
	}

	matrix_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23) {
		mat_val[0][0] = m00;	mat_val[0][1] = m01; mat_val[0][2] = m02; mat_val[0][3] = m03;
		mat_val[1][0] = m10;	mat_val[1][1] = m11; mat_val[1][2] = m12; mat_val[1][3] = m13;
		mat_val[2][0] = m20;	mat_val[2][1] = m21; mat_val[2][2] = m22; mat_val[2][3] = m23;
	}

	void init(const vector3_t& x_axis, const vector3_t& y_axis, const vector3_t& z_axis, const vector3_t& origin) {
		mat_val[0][0] = x_axis.x; mat_val[0][1] = y_axis.x; mat_val[0][2] = z_axis.x; mat_val[0][3] = origin.x;
		mat_val[1][0] = x_axis.y; mat_val[1][1] = y_axis.y; mat_val[1][2] = z_axis.y; mat_val[1][3] = origin.y;
		mat_val[2][0] = x_axis.z; mat_val[2][1] = y_axis.z; mat_val[2][2] = z_axis.z; mat_val[2][3] = origin.z;
	}

	matrix_t(const vector3_t& x_axis, const vector3_t& y_axis, const vector3_t& z_axis, const vector3_t& origin) {
		init(x_axis, y_axis, z_axis, origin);
	}

	inline void set_origin(vector3_t const& p) {
		mat_val[0][3] = p.x;
		mat_val[1][3] = p.y;
		mat_val[2][3] = p.z;
	}

	inline void invalidate(void) {
		for (auto& i : this->mat_val)
			for (float& j : i)
				j = std::numeric_limits<float>::infinity();
	}

	float* operator[](int i) {
		return this->mat_val[i];
	}

	const float* operator[](int i) const {
		return this->mat_val[i];
	}

	float* base() {
		return &this->mat_val[0][0];
	}

	const float* base() const {
		return &this->mat_val[0][0];
	}

	float mat_val[3][4];
};
