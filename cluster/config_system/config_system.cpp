#include "config_system.h"

bool c_config_system::save( const std::string file_name ) {
	const size_t class_size = sizeof( c_config_system );
	void* buffer = std::malloc( class_size );

	std::memcpy( buffer, &g_config_system, class_size );

	std::ofstream output( file_name, std::ios::binary );
	if ( !output.is_open( ) )
		return false;

	output.write( static_cast< const char* >( buffer ), class_size );
	output.flush( );
	output.close( );

	std::free( buffer );
	buffer = NULL;
	return true;
}

bool c_config_system::load( const std::string file_name ) {
	std::ifstream input( file_name, std::ios::binary );
	if ( !input.is_open( ) )
		return false;

	const size_t class_size = sizeof( c_config_system );
	void* buffer = std::malloc( class_size );
	input.read( static_cast< char* >( buffer ), class_size );
	input.close( );

	std::memcpy( &g_config_system, buffer, class_size );
	std::free( buffer );
	buffer = NULL;
	return true;
}

c_config_system g_config_system;