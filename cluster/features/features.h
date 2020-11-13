#pragma once
#include "implementations/menu.h"
#include "implementations/visuals.h"
#include "implementations/thirdperson.h"

class c_features {
public:
	c_menu menu;
	c_visuals visuals;
	c_thirdperson thirdperson;
};

extern c_features g_features;