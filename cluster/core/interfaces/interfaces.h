#pragma once
#include <Windows.h>
#include <string>
#include <d3d9.h>
#include "../../module_manager/module_manager.h"
#include "../../console/console.h"
#include "../../string_utilities/string_utilities.h"

#include "../../../game/interfaces/client_mode.h"
#include "../../../game/interfaces/globals.h"
#include "../../../game/interfaces/client_state.h"
#include "../../../game/interfaces/entity_list.h"
#include "../../../game/interfaces/client.h"
#include "../../../game/interfaces/panel.h"
#include "../../../game/interfaces/model_render.h"
#include "../../../game/interfaces/surface.h"
#include "../../../game/interfaces/engine.h"
#include "../../../game/interfaces/debug_overlay.h"
#include "../../../game/interfaces/convar.h"
#include "../../../game/interfaces/prediction.h"
#include "../../../game/interfaces/input.h"
#include "../../../game/interfaces/trace.h"

class c_interfaces {
public:
	i_client_mode* client_mode;
	i_globals* globals;
	i_client_state* client_state;
	i_entity_list* entity_list;
	i_client* client;
	i_panel* panel;
	IDirect3DDevice9* direct_x;
	void* file_system;
	i_model_render* model_render;
	i_surface* surface;
	i_engine* engine;
	i_debug_overlay* debug_overlay;
	i_convar* convar;
	i_prediction* prediction;
	std::uint8_t* player;
	i_input* input;
	i_trace* trace;


	bool capture_all( );

	template <typename type>
	type* capture_interface( const std::string& module_name, const std::string& interface_name ) {
		std::optional<HMODULE> optional_module_handle = g_module_manager.get_handle( module_name );
		if ( !optional_module_handle.has_value( ) )
			return nullptr;

		using create_interface_fn = void* ( * )( const char*, int* );
		const create_interface_fn create_interface = reinterpret_cast< create_interface_fn >( GetProcAddress( optional_module_handle.value( ), "CreateInterface" ) );

		if ( !create_interface ) {
			g_console.error( "failed to capture %s from %s", g_string_utilities.to_lower( interface_name ).c_str( ), g_string_utilities.to_lower( module_name.c_str( ) ).c_str( ) );
			return nullptr;
		}

		g_console.message( "captured %s from %s", g_string_utilities.to_lower( interface_name ).c_str( ), g_string_utilities.to_lower( module_name ).c_str( ) );
		return static_cast< type* >( create_interface( interface_name.c_str( ), nullptr ) );
	}


};

extern c_interfaces g_interfaces;
