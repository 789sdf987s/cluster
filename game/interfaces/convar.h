#pragma once
#include "../classes/convar.h"

class i_convar {
public:
	c_convar* find_convar( const char* var_name ) {
		using original_fn = c_convar * ( __thiscall* )( i_convar*, const char* );
		return ( *( original_fn** ) this ) [ 14 ]( this, var_name );
	}
};
