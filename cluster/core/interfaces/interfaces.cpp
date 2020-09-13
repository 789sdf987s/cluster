#include "interfaces.h"

bool c_interfaces::capture_all( ) {
	client_mode = this->capture_interface<i_client_mode>( "client.dll", "VClient018" );
	if ( !client_mode )
		return false;

	return true;
}

c_interfaces g_interfaces;