#include "interfaces.h"

bool c_interfaces::capture_all( ) {
	client = this->capture_interface<i_client>( "client.dll", "VClient018" );
	if ( !client )
		return false;

	entity_list = this->capture_interface<i_entity_list>( "client.dll", "VClientEntityList003" );
	if ( !entity_list )
		return false;

	client_mode = **reinterpret_cast< i_client_mode*** >( ( *reinterpret_cast< uintptr_t** >( client ) )[ 10 ] + 5 );
	if ( !client_mode )
		return false;

	globals = **reinterpret_cast< i_globals*** >( ( *reinterpret_cast< uintptr_t** >( client ) )[ 11 ] + 10 );
	if ( !globals )
		return false;

	std::optional<std::uint8_t*> client_state_signature = g_utilities.signature_scan( "engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3" );
	if ( !client_state_signature.has_value( ) )
		return false;

	client_state = **reinterpret_cast< i_client_state*** >( client_state_signature.value( ) + 1 );
	if ( !client_state )
		return false;

	return true;
}

c_interfaces g_interfaces;