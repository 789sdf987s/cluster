#pragma once
#include "../../cluster/vector/vector3.h"

class c_usercmd {
public:
	int pad;
	int command_number;
	int tick_count;
	vector3_t viewangles;
	vector3_t aim_direction;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	char impulse;
	int weapon_select;
	int weapon_subtype;
	int random_seed;
	short mouse_direction_x;
	short mouse_direction_y;
	bool predicted;
};
