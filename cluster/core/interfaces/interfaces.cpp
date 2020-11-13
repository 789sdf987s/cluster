#include "interfaces.h"

bool c_interfaces::capture_all( ) {
	client = this->capture_interface<i_client>( "client.dll", "VClient018" );
	if ( !client )
		return false;

	entity_list = this->capture_interface<i_entity_list>( "client.dll", "VClientEntityList003" );
	if ( !entity_list )
		return false;

	client_mode = **reinterpret_cast< i_client_mode*** >( ( *reinterpret_cast< uintptr_t** >( client ) ) [ 10 ] + 5 );
	if ( !client_mode ) {
		g_console.error( "failed to capture client_mode from client.dll" );
		return false;
	}

	g_console.message( "captured client_mode from client.dll" );

	globals = **reinterpret_cast< i_globals*** >( ( *reinterpret_cast< uintptr_t** >( client ) ) [ 11 ] + 10 );
	if ( !globals ) {
		g_console.error( "failed to capture globals from client.dll" );
		return false;
	}

	g_console.message( "captured globals from client.dll" );

	std::uint8_t* client_state_signature = g_utilities.signature_scan( "engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3" );
	if ( !client_state_signature ) {
		g_console.error( "failed to capture client_state from engine.dll" );
		return false;
	}

	client_state = **reinterpret_cast< i_client_state*** >( client_state_signature + 1 );
	if ( !client_state ) {
		g_console.error( "failed to capture client_state from engine.dll" );
		return false;
	}

	g_console.message( "captured client_state from engine.dll" );

	panel = this->capture_interface<i_panel>( "vgui2.dll", "VGUI_Panel009" );
	if ( !panel )
		return false;

	std::uint8_t* direct_x_signature = g_utilities.signature_scan( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" );
	if ( !direct_x_signature ) {
		g_console.error( "failed to capture direct_x from shaderapidx9.dll" );
		return false;
	}

	direct_x = **reinterpret_cast< IDirect3DDevice9*** >( direct_x_signature + 1 );
	if ( !direct_x ) {
		g_console.error( "failed to capture direct_x from shaderapidx9.dll" );
		return false;
	}

	g_console.message( "captured direct_x from shaderapidx9.dll" );

	file_system = this->capture_interface<void*>( "filesystem_stdio.dll", "VFileSystem017" );
	if ( !file_system )
		return false;

	model_render = this->capture_interface<i_model_render>( "engine.dll", "VEngineModel016" );
	if ( !model_render )
		return false;

	surface = this->capture_interface<i_surface>( "vguimatsurface.dll", "VGUI_Surface031" );
	if ( !surface )
		return false;

	engine = this->capture_interface<i_engine>( "engine.dll", "VEngineClient014" );
	if ( !engine )
		return false;

	debug_overlay = this->capture_interface<i_debug_overlay>( "engine.dll", "VDebugOverlay004" );
	if ( !debug_overlay )
		return false;

	convar = this->capture_interface<i_convar>( "vstdlib.dll", "VEngineCvar007" );
	if ( !convar )
		return false;

	prediction = this->capture_interface<i_prediction>( "client.dll", "VClientPrediction001" );
	if ( !prediction )
		return false;

	player = g_utilities.signature_scan( "client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 89 7C 24 0C" );
	if ( !player ) {
		g_console.error( "failed to capture player from client.dll" );
		return false;
	}

	player += 0x47;

	g_console.message( "captured player" );

	input = *reinterpret_cast< i_input** >( g_utilities.signature_scan( "client.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) + 1 );
	if ( !player ) {
		g_console.error( "failed to capture input from client.dll" );
		return false;
	}

	trace = this->capture_interface<i_trace>( "engine.dll", "EngineTraceClient004" );
	if ( !trace )
		return false;

	return true;
}

c_interfaces g_interfaces;
