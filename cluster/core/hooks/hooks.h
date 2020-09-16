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
	CREATE_HOOK_HEADER( void __fastcall, c_paint_traverse, "paint_traverse", REGISTERS, unsigned int panel, bool force_repaint, bool allow_force );
	CREATE_HOOK_HEADER( long __fastcall, c_end_scene, "end_scene", REGISTERS, IDirect3DDevice9* device );
	CREATE_HOOK_HEADER( long __fastcall, c_reset, "reset", REGISTERS, IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters );

	class c_wnd_proc {
	public:
		static __forceinline void set( ) {
			original = reinterpret_cast< WNDPROC >( SetWindowLongA( FindWindowA( "Valve001", NULL ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hook ) ) );
			g_console.message( "set wnd_proc" );
		}

		static __forceinline void restore( ) {
			SetWindowLongA( FindWindowA( "Valve001", NULL ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( original ) );
		}

		static LRESULT __stdcall hook( HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param );
		static inline WNDPROC original;
	};

	__forceinline void* get_virtual( void* _class, unsigned int index ) {
		return reinterpret_cast< void* >( ( *static_cast< int** >( _class ) )[ index ] );
	}
};

extern c_hooks g_hooks;
