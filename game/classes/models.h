#pragma once
#include "../../cluster/vector/vector3.h"

class matrix_t;

struct model_t {
	void* handle;
	char name [ 260 ];
	int load_flags;
	int server_count;
	int type;
	int flags;
	vector3_t mins;
	vector3_t maxs;
	float radius;
};

struct model_render_info_t {
	vector3_t origin;
	vector3_t angles;
	char pad [ 0x4 ];
	void* renderable;
	const model_t* model;
	const matrix_t* model_to_world;
	const matrix_t* lighting_offset;
	const vector3_t* lighting_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	unsigned short instance;

	model_render_info_t( ) {
		model_to_world = NULL;
		lighting_offset = NULL;
		lighting_origin = NULL;
	}
};
