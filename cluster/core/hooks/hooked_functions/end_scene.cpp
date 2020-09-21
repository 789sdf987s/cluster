#include <mutex>
#include <intrin.h>
#include "../hooks.h"
#include "../../../features/features.h"

long __fastcall c_hooks::c_end_scene::hook( REGISTERS, IDirect3DDevice9* device ) {
	static std::uintptr_t gameoverlay_return_address = 0;

	if ( !gameoverlay_return_address ) {
		MEMORY_BASIC_INFORMATION info;
		VirtualQuery( _ReturnAddress( ), &info, sizeof( MEMORY_BASIC_INFORMATION ) );

		char mod[ MAX_PATH ];
		GetModuleFileNameA( static_cast< HMODULE >( info.AllocationBase ), mod, MAX_PATH );

		if ( strstr( mod, "gameoverlay" ) )
			gameoverlay_return_address = reinterpret_cast< std::uintptr_t >( _ReturnAddress( ) );
	}

	if ( gameoverlay_return_address != reinterpret_cast< std::uintptr_t >( _ReturnAddress( ) ) )
		return original( ecx, edx, device );

	static std::once_flag init_flag;
	std::call_once( init_flag, &c_menu::impl_init, &g_features.menu, FindWindowA( "Valve001", "Counter-Strike: Global Offensive" ), device );

	if ( !g_features.menu.is_open )
		return original( ecx, edx, device );

	g_features.menu.new_frame( );
	{
		g_features.menu.populate_render_list( );
	}
	g_features.menu.end_frame_and_render( );

	return original( ecx, edx, device );
}