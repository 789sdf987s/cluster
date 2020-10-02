#pragma once
#include "material.h"

class i_model_render {
public:
	void override_material(i_material* material) {
		using original_fn = void(__thiscall*)(i_model_render*, i_material*, int, int);
		return (*(original_fn**)this)[1](this, material, 0, 0);
	}
};
