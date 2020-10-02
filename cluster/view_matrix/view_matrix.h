#pragma once
#include "../vector/vector3.h"
#include "../matrix/matrix.h"

typedef float float_t;

class view_matrix_t {
public:

	view_matrix_t();
	view_matrix_t(
		float_t m00, float_t m01, float_t m02, float_t m03,
		float_t m10, float_t m11, float_t m12, float_t m13,
		float_t m20, float_t m21, float_t m22, float_t m23,
		float_t m30, float_t m31, float_t m32, float_t m33
	);

	view_matrix_t(const vector3_t& forward, const vector3_t& left, const vector3_t& up);

	view_matrix_t(const matrix_t& m3x4);

	void init(
		float_t m00, float_t m01, float_t m02, float_t m03,
		float_t m10, float_t m11, float_t m12, float_t m13,
		float_t m20, float_t m21, float_t m22, float_t m23,
		float_t m30, float_t m31, float_t m32, float_t m33
	);

	void init(const matrix_t& matrix3x4);

	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	inline float* base() {
		return &m[0][0];
	}

	inline const float* base() const {
		return &m[0][0];
	}

	void		set_left(const vector3_t& left);
	void		set_up(const vector3_t& up);
	void		set_forward(const vector3_t& forward);

	void		get_basis_vector_3d(vector3_t& forward, vector3_t& left, vector3_t& up) const;
	void		set_basis_vector_3d(const vector3_t& forward, const vector3_t& left, const vector3_t& up);

	vector3_t& get_translation(vector3_t& trans) const;
	void		set_translation(const vector3_t& trans);

	void		pre_translate(const vector3_t& tans);
	void		post_translate(const vector3_t& trans);

	matrix_t& as_matrix();
	const matrix_t& as_matrix() const;
	void		copy_from_matrix(const matrix_t& m3x4);
	void		set_matrix(matrix_t& m3x4) const;

	bool		operator==(const view_matrix_t& src) const;
	bool		operator!=(const view_matrix_t& src) const { return !(*this == src); }

	vector3_t		get_left() const;
	vector3_t		get_up() const;
	vector3_t		get_forward() const;
	vector3_t		get_translation() const;

	void		vector_3d_multiply(const vector3_t& in, vector3_t& out) const;
	vector3_t		apply_rotation(const vector3_t& vec) const;
	vector3_t		operator*(const vector3_t& vec) const;
	vector3_t		vector_3d_multiply(const vector3_t& vec) const;
	vector3_t		vector_3d_transpose_rotation(const vector3_t& vec) const;
	vector3_t		vector_3d_multiply_upper(const vector3_t& vec) const;
	vector3_t		vector_3d_transpose(const vector3_t& vec) const;

	view_matrix_t& operator=(const view_matrix_t& other);
	void		MatrixMul(const view_matrix_t& vm, view_matrix_t& out) const;
	const view_matrix_t& operator+=(const view_matrix_t& other);
	view_matrix_t		operator*(const view_matrix_t& other) const;
	view_matrix_t		operator+(const view_matrix_t& other) const;
	view_matrix_t		operator-(const view_matrix_t& other) const;
	view_matrix_t		operator-() const;

	void		identity();
	bool		is_identity() const;
	void		setup_maitrx_orginal_angles(const vector3_t& origin, const vector3_t& angles);
	void		inverse_tr(view_matrix_t& ret) const;
	bool		is_rotation_matrix() const;
	view_matrix_t		inverse_tr() const;
	vector3_t			get_scale() const;
	view_matrix_t		scale(const vector3_t& scale);
	view_matrix_t		normalize_basis_vector_3d() const;
	view_matrix_t		transpose() const;
	view_matrix_t		transpose_3x3() const;
	float_t	m[4][4];
};

