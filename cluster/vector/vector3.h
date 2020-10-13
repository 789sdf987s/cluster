#pragma once
#include <cmath>

class vector3_t {
public:
	float x, y, z;

	inline void init(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline vector3_t() {
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
	}

	inline vector3_t(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline vector3_t& operator+=(const vector3_t& other) {
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	inline vector3_t& operator-=(const vector3_t& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	inline vector3_t& operator*=(float fl) {
		x *= fl;
		y *= fl;
		z *= fl;

		return *this;
	}

	inline vector3_t operator+(const vector3_t& other) {
		return { x + other.x, y + other.y, z + other.z };
	}

	inline vector3_t operator-(const vector3_t& other) {
		return { x - other.x, y - other.y, z - other.z };
	}

	auto operator-(const vector3_t& other) const -> vector3_t {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	inline vector3_t operator*(float fl) {
		return { x * fl, y * fl, z * fl };
	}

	inline vector3_t operator*(const vector3_t& other) {
		return { x * other.x, y * other.y, z * other.z };
	}

	inline vector3_t& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;

		return *this;
	}

	inline auto operator/(float other) {
		vector3_t buf;

		buf.x = x / other;
		buf.y = y / other;
		buf.z = z / other;

		return buf;
	}

	inline float& operator[](int i) {
		return ((float*)this)[i];
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline float length_2d() {
		return sqrt((x * x) + (y * y));
	}

	inline float length_squared() {
		auto square = [](float n) {
			return static_cast<float>(n * n);
		};

		return (square(x) + square(y) + square(z));
	}

	inline float dot(const float* other) {
		const vector3_t& a = *this;

		return(a.x * other[0] + a.y * other[1] + a.z * other[2]);
	}
};
