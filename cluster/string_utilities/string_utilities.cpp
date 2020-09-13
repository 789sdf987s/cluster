#include "string_utilities.h"

std::string c_string_utilities::to_lower( std::string str ) {
	std::transform( str.begin( ), str.end( ), str.begin( ),
		[ ]( unsigned char c ) { return std::tolower( c ); } );

	return str;
}

c_string_utilities g_string_utilities;