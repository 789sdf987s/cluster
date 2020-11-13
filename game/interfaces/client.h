#pragma once
#include "../classes/client_class.h"

class i_client {
public:
	virtual int	connect( void* appsystem_factory, void* globals ) = 0;
	virtual void disconnect( ) = 0;

	virtual int	init( void* app_system_factory, void* globals ) = 0;
	virtual void post_init( ) = 0;

	virtual void shutdown( void ) = 0;

	virtual void level_init_pre_entity( char const* map_name ) = 0;
	virtual void level_init_post_entity( ) = 0;

	virtual void level_shutdown( void ) = 0;

	virtual c_client_class* get_client_classes( void ) = 0;

	virtual int	hud_vid_init( void ) = 0;
	virtual void hud_process_input( bool active ) = 0;
	virtual void hud_update( bool active ) = 0;
	virtual void hud_reset( void ) = 0;
	virtual void hud_text( const char* message ) = 0;
};