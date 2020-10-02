#pragma once
#include "implementations/menu.h"
#include "implementations/visuals.h"

class c_features {
public:
	c_menu menu;
	c_visuals visuals;
};

extern c_features g_features;