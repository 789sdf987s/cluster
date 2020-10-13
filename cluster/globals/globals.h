#pragma once
#include "../../game/classes/entities.h"

class c_globals {
public:
	player_t* local_player;
	vector3_t thirdperson_angles;
};

extern c_globals g_globals;