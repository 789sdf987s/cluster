#pragma once
#include "../../cluster/vector/vector3.h"
#include "../classes/entities.h"
#include "../classes/usercmd.h"

class i_prediction {
public:
	unsigned char pad0[0x4];
	unsigned int last_ground;
	bool in_prediction;
	bool old_cl_predict_value;
	bool engine_paused;
	unsigned char pad2[0xD];
	bool is_first_time_predicted;

	void update(int start_frame, bool valid_frame, int incoming_acknowledged, int outgoing_command) {
		using original_fn = void* (__thiscall*)(i_prediction*, int, bool, int, int);
		(*(original_fn**)this)[3](this, start_frame, valid_frame, incoming_acknowledged, outgoing_command);
	}

	void get_local_view_angles(vector3_t& view) {
		using original_fn = void* (__thiscall*)(i_prediction*, vector3_t&);
		(*(original_fn**)this)[12](this, view);
	}

	void set_local_view_angles(vector3_t& view) {
		using original_fn = void* (__thiscall*)(i_prediction*, vector3_t&);
		(*(original_fn**)this)[13](this, view);
	}

	void check_moving_ground(entity_t* entity, double frametime) {
		using original_fn = void* (__thiscall*)(i_prediction*, entity_t*, double);
		(*(original_fn**)this)[18](this, entity, frametime);
	}

	void setup_move(entity_t* entity, c_usercmd* cmd, void* helper, void* move_data) {
		using original_fn = void* (__thiscall*)(i_prediction*, entity_t*, c_usercmd*, void*, void*);
		(*(original_fn**)this)[20](this, entity, cmd, helper, move_data);
	}

	void finish_move(entity_t* entity, c_usercmd* cmd, void* move_data) {
		using original_fn = void* (__thiscall*)(i_prediction*, entity_t*, c_usercmd*, void*);
		(*(original_fn**)this)[21](this, entity, cmd, move_data);
	}
};
