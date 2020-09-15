#pragma once
#include <Windows.h>
#include <string>
#include "../../module_manager/module_manager.h"
#include "../../console/console.h"

#include "../../../game/interfaces/client_mode.h"
#include "../../../game/interfaces/globals.h"
#include "../../../game/interfaces/client_state.h"
#include "../../../game/interfaces/entity_list.h"
#include "../../../game/interfaces/client.h"

class c_interfaces {
public:
	i_client_mode* client_mode;
	i_globals* globals;
	i_client_state* client_state;
	i_entity_list* entity_list;
	i_client* client;

	bool capture_all( );

	template <typename type>
	type* capture_interface( const std::string& module_name, const std::string& interface_name ) {
		std::optional<HMODULE> optional_module_handle = g_module_manager.get_handle( module_name );
		if ( !optional_module_handle.has_value( ) )
			return nullptr;

		using create_interface_fn = void* ( * )( const char*, int* );
		const create_interface_fn create_interface = reinterpret_cast< create_interface_fn >( GetProcAddress( optional_module_handle.value( ), "CreateInterface" ) );

		if ( !create_interface ) {
			g_console.error( "failed to capture interface %s from %s", interface_name.c_str( ), module_name.c_str( ) );
			return nullptr;
		}

		g_console.message( "captured interface %s from %s", interface_name.c_str( ), module_name.c_str( ) );
		return static_cast< type* >( create_interface( interface_name.c_str( ), nullptr ) );
	}
};

extern c_interfaces g_interfaces;