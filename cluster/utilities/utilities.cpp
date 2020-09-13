#include "utilities.h"

bool c_utilities::create_thread( THREAD_FUNCTION function( void* ), void* parameter ) {
	HANDLE thread_handle = CreateThread( NULL, 0, function, parameter, 0, NULL );
	if ( thread_handle == NULL )
		return false;

	CloseHandle( thread_handle );
	return true;
}

void c_utilities::wait_for_modules( const std::vector<std::string>& modules ) {
	unsigned short found_modules;

	do {
		found_modules = 0;

		for ( const std::string& current_module_name : modules ) {
			HMODULE current_module_handle = GetModuleHandleA( current_module_name.c_str( ) );

			if ( current_module_handle != NULL ) {
				CloseHandle( current_module_handle );
				found_modules++;
			}
		}

		this->sleep( MODULE_WAIT_CHECK_DELAY );
	} while ( found_modules != modules.size( ) );
}

void c_utilities::sleep( unsigned int ms ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
}

void c_utilities::critical_error( const std::string& message ) {
	MessageBoxA( NULL, message.c_str( ), "critical error", MB_OK );
	_Exit( EXIT_FAILURE );
}

c_utilities g_utilities;