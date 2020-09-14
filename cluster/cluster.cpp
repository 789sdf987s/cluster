#include "cluster.h"

THREAD_FUNCTION c_cluster::load( void* parameter ) {
	g_cluster.module_handle = static_cast< HMODULE >( parameter );

	if ( !g_console.create_console( "cluster" ) )
		g_utilities.critical_error( "failed to create console" );

	g_console.special( "loading cluster, built at %s on %s", g_string_utilities.to_lower( __DATE__ ).c_str( ), g_string_utilities.to_lower( __TIME__ ).c_str( ) );
	g_utilities.wait_for_modules( { "client.dll", "serverbrowser.dll" } );
	g_console.message( "found required modules" );

	if ( !g_interfaces.capture_all( ) ) {
		g_console.error( "failed to capture interfaces" );
		FreeLibraryAndExitThread( g_cluster.module_handle, EXIT_FAILURE );
		return EXIT_FAILURE;
	}

	g_console.message( "captured interfaces" );

	if ( !g_hooks.hook_all( ) ) {
		g_console.error( "failed to hook functions" );
		g_hooks.unhook_all( );
		FreeLibraryAndExitThread( g_cluster.module_handle, EXIT_FAILURE );
		return EXIT_FAILURE;
	}

	g_console.message( "hooked functions" );

	g_cluster.is_loaded = true;
	return EXIT_SUCCESS;
}

void c_cluster::unload( ) {
	if ( !g_cluster.is_loaded )
		return;

	g_hooks.unhook_all( );
}

c_cluster g_cluster;
