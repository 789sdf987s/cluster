#pragma once
#include "utilities/utilities.h"
#include "console/console.h"
#include "string_utilities/string_utilities.h"
#include "core/interfaces/interfaces.h"
#include "core/hooks/hooks.h"

class c_cluster {
public:
	bool is_loaded;
	HMODULE module_handle;

	static THREAD_FUNCTION load( void* parameter );
	void unload( );
};

extern c_cluster g_cluster;