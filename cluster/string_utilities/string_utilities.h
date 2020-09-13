#pragma once
#include <string>
#include <algorithm>

class c_string_utilities {
public:
	std::string to_lower( std::string str );
};

extern c_string_utilities g_string_utilities;