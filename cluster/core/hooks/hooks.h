#pragma once
#include "../../../dependencies/minhook/MinHook.h"
#include "../interfaces/interfaces.h"
#include "../../../game/classes/usercmd.h"

#define REGISTERS void* ecx, void* edx
#define CREATE_HOOK_HEADER(type, class_name, name, parameters, ...)  class class_name { \
													public: \
														static type hook( parameters, __VA_ARGS__ ); \
														static inline decltype( &hook ) original; \
														static inline bool create_hook( void* to_hook ) { \
															bool success = MH_CreateHook( to_hook, &hook, reinterpret_cast< void** >( &original )) == MH_OK; \
															if ( success ) \
																g_console.message( "hooked %s", name ); \
															else \
																g_console.error( "failed to hook %s", name ); \
															return success; \
														} \
													}

class c_hooks {
public:
	bool hook_all( );
	void unhook_all( );

	CREATE_HOOK_HEADER( bool __fastcall, c_create_move, "create_move", REGISTERS, float input_sample_frametime, c_usercmd* cmd );

	inline void* get_virtual( void* _class, unsigned int index ) {
		return reinterpret_cast< void* >( ( *static_cast< int** >( _class ) )[ index ] );
	}
};

extern c_hooks g_hooks;
