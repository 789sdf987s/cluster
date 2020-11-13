#pragma once
#include <string>
#include <algorithm>

class c_string_utilities {
public:
	inline std::string to_lower( std::string str ) {
		std::transform( str.begin( ), str.end( ), str.begin( ),
			[ ] ( unsigned char c ) { return std::tolower( c ); } );

		return str;
	}
};

extern c_string_utilities g_string_utilities;